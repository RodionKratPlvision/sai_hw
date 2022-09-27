#include <stdio.h>
#include "sai.h"

const char* test_profile_get_value(
    _In_ sai_switch_profile_id_t profile_id,
    _In_ const char* variable)
{
    return 0;
}

int test_profile_get_next_value(
    _In_ sai_switch_profile_id_t profile_id,
    _Out_ const char** variable,
    _Out_ const char** value)
{
    return -1;
}

const service_method_table_t test_services = {
    test_profile_get_value,
    test_profile_get_next_value
};

int main()
{
    sai_status_t              status;
    sai_switch_api_t         *switch_api;
    sai_object_id_t           vr_oid;
    sai_attribute_t           attrs[2];
    sai_switch_notification_t notifications;
    sai_object_id_t           port_list[64];

    sai_lag_api_t            *lag_api;
    sai_object_id_t          *lag_oid_0;
    sai_object_id_t          *lag_oid_1;
    sai_object_id_t          *lag_member_oid_0;
    sai_attribute_t           member_attrs_0[2];
    sai_object_id_t          *lag_member_oid_1;
    sai_attribute_t           member_attrs_1[2];
    sai_object_id_t          *lag_member_oid_2;
    sai_attribute_t           member_attrs_2[2];
    sai_object_id_t          *lag_member_oid_3;
    sai_attribute_t           member_attrs_3[2];
	
    status = sai_api_initialize(0, &test_services);
    status = sai_api_query(SAI_API_SWITCH, (void**)&switch_api);

    status = switch_api->initialize_switch(0, "HW_ID", 0, &notifications);
    attrs[0].id = SAI_SWITCH_ATTR_PORT_LIST;
    attrs[0].value.objlist.list = port_list;
    attrs[0].value.objlist.count = 64;
    status = switch_api->get_switch_attribute(1, attrs);
    
    status = sai_api_query(SAI_API_LAG, (void**)&lag_api);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to query LAG API, status=%d\n", status);
        return 1;
    }

    // STEP 1 
    
    status = lag_api->create_lag(&lag_oid_0, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG, status=%d\n", status);
        return 1;
    }

    // STEP 2

    member_attrs_0[0].id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    member_attrs_0[0].value.oid = lag_oid_0;
    member_attrs_0[1].id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    member_attrs_0[1].value.oid = port_list[0];

    status = lag_api->create_lag_member(&lag_member_oid_0, 2, member_attrs_0);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    // STEP 3

    member_attrs_1[0].id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    member_attrs_1[0].value.oid = lag_oid_0;
    member_attrs_1[1].id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    member_attrs_1[1].value.oid = port_list[1];

    status = lag_api->create_lag_member(&lag_member_oid_1, 2, member_attrs_1);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    // STEP 4

    status = lag_api->create_lag(&lag_oid_1, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG, status=%d\n", status);
        return 1;
    }

    // STEP 5

    member_attrs_2[0].id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    member_attrs_2[0].value.oid = lag_oid_1;
    member_attrs_2[1].id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    member_attrs_2[1].value.oid = port_list[2];

    status = lag_api->create_lag_member(&lag_member_oid_2, 2, member_attrs_2);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    // STEP 6

    member_attrs_3[0].id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    member_attrs_3[0].value.oid = lag_oid_1;
    member_attrs_3[1].id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    member_attrs_3[1].value.oid = port_list[3];

    status = lag_api->create_lag_member(&lag_member_oid_3, 2, member_attrs_3);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    // STEP 7

    status = lag_api->get_lag_attribute(lag_oid_0, 1, port_list);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get a LAG attribure, status=%d\n", status);
        return 1;
    }

    // STEP 8

    status = lag_api->get_lag_attribute(lag_oid_1, 1, port_list);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get a LAG attribure, status=%d\n", status);
        return 1;
    }

    // STEP 9

    status = lag_api->get_lag_member_attribute(lag_member_oid_0, 1, member_attrs_3[0].value.oid);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get a LAG_MEMBER attribure, status=%d\n", status);
        return 1;
    }
    
    // STEP 10

    status = lag_api->get_lag_member_attribute(lag_member_oid_2, 1, member_attrs_2[1].value.oid);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get a LAG_MEMBER attribure, status=%d\n", status);
        return 1;
    }
    
    // STEP 11

    status = lag_api->remove_lag_member(lag_member_oid_1);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove a LAG_MEMBER, status=%d\n", status);
        return 1;
    }
    
    // STEP 12

    status = lag_api->get_lag_attribute(lag_oid_0, 1, port_list);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get a LAG attribure, status=%d\n", status);
        return 1;
    }
    
    // STEP 13

    status = lag_api->remove_lag_member(lag_member_oid_2);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove a LAG_MEMBER, status=%d\n", status);
        return 1;
    }
    
    // STEP 14

    status = lag_api->get_lag_attribute(lag_oid_1, 1, port_list);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get a LAG attribure, status=%d\n", status);
        return 1;
    }
    
    // STEP 15

    status = lag_api->remove_lag_member(lag_member_oid_0);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove a LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    // STEP 16

    status = lag_api->remove_lag_member(lag_member_oid_3);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove a LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    // STEP 17

    status = lag_api->remove_lag(lag_oid_1);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove a LAG, status=%d\n", status);
        return 1;
    }

    // STEP 18

    status = lag_api->remove_lag(lag_oid_0);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove a LAG, status=%d\n", status);
        return 1;
    }

    return 0;
}
