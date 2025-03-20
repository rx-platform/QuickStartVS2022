#include "pch.h"
#include "plugin_version.h"
#include "PogadjanjeBrojeva.h"


rx_node_id PogadjanjeBrojeva::source_type_id = rx_node_id::from_string("g:9A261F5C-F145-4742-8B17-622FF02981A2");

PogadjanjeBrojeva::PogadjanjeBrojeva()
	: rx_platform_api::rx_source(true /*this is input source?*/, true/*this is output source?*/)
	, timer_(0)
{

}
PogadjanjeBrojeva::~PogadjanjeBrojeva()
{

}
// called on initialization
// executing in meta context
// init static stuff here
rx_result PogadjanjeBrojeva::initialize_source(rx_platform_api::rx_init_context& ctx)
{
	RX_PLUGIN_LOG_DEBUG("Brojevi", 100, _rx_func_);
	rx_result result = timeout_.bind(".Timeout", ctx, [this](const uint32_t val)
		{
			/*if (timer_)
				start_timer(timer_, val);*/
		});
	if (!result)
		return result;

	result = imagined_.bind(".ZamisljeniBroj", ctx);
	if (!result)
		return result;

	return true;
}
// called on start
// executing in runtime context
// start dynamic things here
rx_result PogadjanjeBrojeva::start_source(rx_platform_api::rx_start_context& ctx)
{
	RX_PLUGIN_LOG_DEBUG("first_source", 100, _rx_func_);

	values::rx_value val;
	val.assign_static<string_type>("Upisi 0", rx_time::now());
	val.set_good_locally();
	source_value_changed(std::move(val));

	timer_ = ctx.create_timer([this]()
		{
			TajmerFukncija();

		}, 0);

	return true;
}
// called on stop
// executing in runtime context
// stop dynamic things here
rx_result PogadjanjeBrojeva::stop_source()
{
	if (timer_)
	{
		destroy_timer(timer_);
	}
	return true;
}
// called on destroy
// executing in meta context
// free static stuff here
rx_result PogadjanjeBrojeva::deinitialize_source()
{
	return true;
}
// write in this source
// id - transaction id if callback is needed in the future
// test - this is a test write
// identity - security identity of the user
// val - value to write
// ctx - process context
rx_result PogadjanjeBrojeva::source_write(runtime_transaction_id_t id, bool test, rx_security_handle_t identity, rx_simple_value val, rx_platform_api::rx_process_context& ctx)
{
	if (!val.convert_to(RX_UINT32_TYPE))
	{
		return RX_INVALID_CONVERSION;
	}
	string_type resp;
	uint32_t broj = val.extract_static<uint32_t>(0);
	if (broj == 0)
	{
		uint32_t zamisljen = rx_border_rand(1, 100);
		imagined_ = zamisljen;
		resp = "Zamislio sam broj izmedju 1 i 100. Koji?";
		start_timer(timer_, timeout_);
	}
	else if(broj>100)
	{
		resp = "Do broja 100 rekoh!";
		start_timer(timer_, timeout_);
	}
	else if (imagined_ > 0)
	{
		start_timer(timer_, timeout_);

		if (broj > imagined_)
		{
			resp = "Moj broj je manji!";
		}
		else if (broj < imagined_)
		{
			resp = "Moj broj je veci!";
		}
		else // broj == imagined_
		{
			resp = "Svaka cast! Upisi 0.";
			suspend_timer(timer_);
			imagined_ = 0;
		}
	}

	if (!resp.empty())
	{
		values::rx_value val;
		val.assign_static<string_type>(resp, rx_time::now());
		val.set_good_locally();
		source_value_changed(std::move(val));
	}
	source_result_received(true, id);
	return true;
}

void PogadjanjeBrojeva::TajmerFukncija()
{
	suspend_timer(timer_);
	if (imagined_ > 0)
	{
		values::rx_value val;
		val.assign_static<string_type>("Ajde vise!!!", rx_time::now());
		val.set_good_locally();
		source_value_changed(std::move(val));
	}
}
