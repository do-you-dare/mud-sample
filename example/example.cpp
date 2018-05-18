#include <mud/mud.h>
#include <example/example.h>
#include <example/Generated/Module.h>
#include <math/Generated/Convert.h>

MyObject::MyObject(ShapeType shape, Colour colour)
	: m_shape(shape)
	, m_colour(colour)
{}

int MyObject::method()
{
	printf("MyObject::method() called !\n");
	return m_number;
};

void foo(int arg)
{
	printf("foo() called !\n");
}

void bar(MyObject& object)
{
	printf("bar() called !\n");
}

Material& colour_material(GfxSystem& gfx_system, Colour& colour)
{
	uint32_t abgr = to_abgr(colour);
	static std::map<uint32_t, Material> materials;
	if(materials.find(abgr) == materials.end())
	{
		materials[abgr] = { to_string(colour).c_str(), "pbr/pbr" };
		PbrMaterialBlock& pbr = materials[abgr].m_pbr_block;
		pbr.m_enabled = true;
		pbr.m_albedo.m_value = colour;
		pbr.m_roughness.m_value = 0.f;
		pbr.m_metallic.m_value = 0.4f;
		pbr.m_roughness.m_value = 0.35f;
	}
	return materials[abgr];
}

void ex_00_tutorial_pump(Shell& app, Widget& parent, Dockbar& dockbar)
{
	static std::vector<Var> objects = { var(MyObject(ShapeType::Sphere, Colour::Pink)) };
	static size_t selected = SIZE_MAX;

	Widget& board = ui::board(parent);
	Widget& left_side = ui::layout_span(board, 0.8f);

	SceneViewer& viewer = ui::scene_viewer(left_side);
	ui::orbit_controller(viewer);

	Widget& lower_side = ui::layout_span(left_side, 0.4f);
	multi_inspector(lower_side, type<MyObject>(), objects, selected);

	Gnode& groot = viewer.m_scene.m_graph.begin();
	gfx::radiance(groot, "radiance/tiber_1_1k.hdr", BackgroundMode::None);
	//gfx::sun_light(groot, 0.f, M_PI / 4.f);

	for(Var& object : objects)
	{
		MyObject& myobject = val<MyObject>(object);
		Gnode& node = gfx::node(groot, &myobject, myobject.m_position);
		Material& material = colour_material(*app.m_gfx_system, myobject.m_colour);
		if(myobject.m_shape == ShapeType::Sphere)
			gfx::shape(node, Sphere(), Symbol(Colour::None, myobject.m_colour), 0U, &material);
		if(myobject.m_shape == ShapeType::Cube)
			gfx::shape(node, Cube(), Symbol(Colour::None, myobject.m_colour), 0U, &material);
	}

	if(selected != SIZE_MAX)
	{
		MyObject& myobject = val<MyObject>(objects[selected]);
		Widget& right_side = ui::layout_span(board, 0.2f);
		inspector(right_side, &myobject);

		Transform transform;
		transform.m_position = myobject.m_position;
		//app.m_editor.m_current_viewer = &viewer;
		//app.m_editor.m_selection = { objects[selected] };
		app.m_editor.set_tool(app.m_editor.m_translate_tool, viewer);
		app.m_editor.m_translate_tool.process(viewer, { &transform });

		myobject.m_position = transform.m_position;
	}
}

#ifdef _EXAMPLE_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_00_tutorial_pump(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	example::module();
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif
