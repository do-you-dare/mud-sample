#ifndef MUD_SHADER_LIGHT
#define MUD_SHADER_LIGHT

#include <common.sh>
#include <pbr/pbr.sh>

uniform vec4 u_light_position_range[MAX_LIGHTS];
uniform vec4 u_light_energy_specular[MAX_LIGHTS];
uniform vec4 u_light_direction_attenuation[MAX_LIGHTS];
uniform vec4 u_light_shadow[MAX_LIGHTS];
uniform mat4 u_light_shadow_matrix[MAX_LIGHTS];
uniform vec4 u_light_spot_params[MAX_LIGHTS];

#ifdef DIRECTIONAL_LIGHT
uniform mat4 u_csm_matrix[4];
uniform vec4 u_csm_splits;
#endif

uniform vec4 u_light_counts;
uniform vec4 u_light_indices[MAX_LIGHTS];

#define LIGHT_TYPE_DIRECTIONAL 0
#define LIGHT_TYPE_OMNI 1
#define LIGHT_TYPE_SPOT 2

struct Light
{
    vec3 position;
    float range;
    vec3 energy;
    float specular;
    vec3 direction;
    float attenuation;
    vec3 shadow_color;
    bool shadows;
    float spot_attenuation;
    float spot_cutoff;
    
    vec3 ray;
    
    float NoL;
    float NoH;
    float LoH;

    float LoV;
    float XoH;
    float YoH;

	float RoV;
};

Light preread_light(int index, Fragment fragment)
{
    Light light;
    light.position = u_light_position_range[index].xyz;
    light.range = u_light_position_range[index].w;
    light.energy = u_light_energy_specular[index].xyz;
	light.specular = u_light_energy_specular[index].w;
    light.direction = u_light_direction_attenuation[index].xyz;
    light.attenuation = u_light_direction_attenuation[index].w;
    light.shadow_color = u_light_shadow[index].xyz;
    light.shadows = bool(u_light_shadow[index].w);
	light.spot_attenuation = u_light_spot_params[index].x;
	light.spot_cutoff = u_light_spot_params[index].y;
    
    return light;
}

void precalc_light(Fragment fragment, inout Light light)
{
    vec3 V = fragment.view;
    vec3 N = fragment.normal;
    vec3 B = fragment.binormal;
    vec3 T = fragment.tangent;
    vec3 L = normalize(light.ray);
    vec3 H = normalize(V + L);
	vec3 R = normalize(-reflect(L, N));
    
    light.NoL = max(dot(N, L), 0.0);
    light.NoH = max(dot(N, H), 0.0);
    light.LoH = max(dot(L, H), 0.0);
    
    light.LoV = dot(L, V);
    light.XoH = dot(T, H);
    light.YoH = dot(B, H);
    
	light.RoV = max(dot(R, V), 0.0);
}

Light read_infinite_light(int index, Fragment fragment)
{
    Light light = preread_light(index, fragment);
    light.ray = -light.direction;
    precalc_light(fragment, light);
    return light;
}

Light read_placed_light(int index, Fragment fragment)
{
    Light light = preread_light(index, fragment);
    light.ray = light.position - fragment.position;
    precalc_light(fragment, light);
    return light;
}

vec3 omni_attenuation(vec3 light, float range, float attenuation_factor, float lower_bound)
{
	float normalized_distance = length(light) / range;
    float attenuation = pow(max(1.0 - normalized_distance, lower_bound), attenuation_factor);
	return vec3_splat(attenuation);
}

vec3 spot_attenuation(vec3 light, vec3 spot_direction, float range, float attenuation_factor, float spot_attenuation, float spot_cutoff)
{
	vec3 attenuation = omni_attenuation(light, range, attenuation_factor, 0.001);
	float scos = max(dot(normalize(light), -spot_direction), spot_cutoff);
	float spot_rim = (1.0 - scos) / (1.0 - spot_cutoff);
	return attenuation * (1.0 - pow(max(spot_rim, 0.001), spot_attenuation));
}

vec3 omni_attenuation(Light light)
{
    return omni_attenuation(light.ray, light.range, light.attenuation, 0.0);
}

vec3 spot_attenuation(Light light)
{
    return spot_attenuation(light.ray, light.direction, light.range, light.attenuation, light.spot_attenuation, light.spot_cutoff);
}

#include "light_brdf.sh"
#include "shadow.sh"

void apply_lights(Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular)
{
	for(int i = 0; i < int(u_light_counts[LIGHT_TYPE_OMNI]); i++)
	{
        Light light = read_placed_light(int(u_light_indices[i][LIGHT_TYPE_OMNI]), fragment);
        light_brdf(light, fragment, material, omni_attenuation(light), diffuse, specular);
	}

	for(int j = 0; j < int(u_light_counts[LIGHT_TYPE_SPOT]); j++)
	{
        Light light = read_placed_light(int(u_light_indices[j][LIGHT_TYPE_SPOT]), fragment);
        light_brdf(light, fragment, material, spot_attenuation(light), diffuse, specular);
	}
}

#ifdef DIRECTIONAL_LIGHT
void directional_light(Fragment fragment, Material material, float frag_w, inout vec3 diffuse, inout vec3 specular)
{
    Light light = read_infinite_light(0, fragment);
    
#ifdef CSM_SHADOW
    vec3 attenuation = csm_shadow(light, fragment.position, fragment.normal, frag_w);
#else
	vec3 attenuation = vec3_splat(1.0);
#endif

	light_brdf(light, fragment, material, attenuation, diffuse, specular);
}
#endif

#endif
