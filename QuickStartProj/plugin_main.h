#pragma once
class plugin_main : public rx_platform_api::rx_platform_plugin
{
public:
	plugin_main();
	~plugin_main();

	rx_result init_plugin();
	rx_result deinit_plugin();

	rx_result build_plugin();
};

