require 'mxx_ru/cpp'
require '../template/frl.test.template'

MxxRu::Cpp::exe_target("frl.test.fs_fn.release.rb")\
{
	required_prj( "frl.lib.release.rb" )
	test_setup()

	target("test_fs_fn")
	include_path("../../../test/fs_fn")
	runtime_mode( MxxRu::Cpp::RUNTIME_RELEASE )
	rtl_mode( MxxRu::Cpp::RTL_STATIC )
	threading_mode( MxxRu::Cpp::THREADING_MULTI )
	obj_placement( MxxRu::Cpp::CustomSubdirObjPlacement.new( "../../../output/test/fs_fn",\
	"../../../output/test/fs_fn/obj/#{mxx_runtime_mode}/1/2/3" ) )
	cpp_sources Dir.glob( "../../../test/fs_fn/**/*.cpp" )
}
