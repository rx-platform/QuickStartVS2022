#pragma once
class PogadjanjeBrojeva : public rx_platform_api::rx_source
{
    DECLARE_PLUGIN_CODE_INFO(1, 0, 0, "\
First Source. Source implementation in test plugin.");

    DECLARE_REFERENCE_PTR(PogadjanjeBrojeva);
public:
    PogadjanjeBrojeva();
    ~PogadjanjeBrojeva();

    rx_result initialize_source(rx_platform_api::rx_init_context& ctx);
    rx_result start_source(rx_platform_api::rx_start_context& ctx);
    rx_result stop_source();
    rx_result deinitialize_source();

    rx_result source_write(runtime_transaction_id_t id, bool test, rx_security_handle_t identity, rx_simple_value val, rx_platform_api::rx_process_context& ctx);

    static rx_node_id source_type_id;

private:
    rx_platform_api::local_value<uint32_t> timeout_;
    rx_platform_api::owned_value<uint32_t> imagined_;

    runtime_handle_t timer_;
    void TajmerFukncija();

};

