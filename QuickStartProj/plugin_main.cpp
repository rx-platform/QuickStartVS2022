#include "pch.h"
#include "plugin_main.h"
#include "plugin_version.h"
#include "plugin_meta.h"
#include "rx_configuration.h"
#include "PogadjanjeBrojeva.h"


RX_DECLARE_PLUGIN(plugin_main);


plugin_main::plugin_main()
{
	
}
plugin_main::~plugin_main()
{

}

rx_result plugin_main::init_plugin()
{
	rx_result result = rx_platform_api::register_source_runtime<PogadjanjeBrojeva>(PogadjanjeBrojeva::source_type_id);
	if (!result)
		return result;

	return true;
}
rx_result plugin_main::deinit_plugin()
{
	return true;
}

rx_result plugin_main::build_plugin()
{
	rx_result result = rx_platform_api::register_item_binary_with_code<PogadjanjeBrojeva>("PogadjanjeBrojeva", "PodFolder"
		, PogadjanjeBrojeva::source_type_id, RX_VARIABLE_SOURCE_TYPE_ID, c_def_PogadjanjeBrojeva, sizeof(c_def_PogadjanjeBrojeva), 0x20005);
	if (!result)
		return result;

	return true;
}