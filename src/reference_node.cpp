#include <string>
#include <vector>
#include "ros/ros.h"

#include "reference_manager/referencer.h"
#include "reference_manager/error_code.h"

#include "iot_bridge/standard_service.h"

using namespace std;

Referencer referencer;

bool reference_handle(iot_bridge::standard_service::Request  &req,
                      iot_bridge::standard_service::Response &res)
{
  bool done = false;
  res.value = "";
  res.code = OTHER;

  if(req.action == "reference")
  {
    size_t pos= req.param.find(":");
    if(pos != string::npos)
    {
      string id = req.param.substr(0, pos);
      string ref = req.param.substr(pos+1, string::npos);
      done = referencer.add_reference(id, ref);
      if(done)
        res.code = NO_ERROR;
      else
        res.code = REF_ALREADY_USED;
    }
  }
  else if(req.action == "unreference")
  {
    done = referencer.remove_reference(req.param);
    if(done)
      res.code = NO_ERROR;
    else
      res.code = UNREFERENCED_ID;
  }
  else if(req.action == "is_referenced")
  {
    done = referencer.is_referenced(req.param);
    if(done)
      res.code = NO_ERROR;
    else
      res.code = UNKNOW_REF;
  }
  else if(req.action == "get_id")
  {
    string id = "";
    done = referencer.get_identifier(req.param, id);
    if(done)
    {
      res.code = NO_ERROR;
      res.value = id;
    }
    else
      res.code = UNKNOW_REF;
  }
  else if(req.action == "get_ref")
  {
    string ref = "";
    done = referencer.get_reference(req.param, ref);
    if(done)
    {
      res.code = NO_ERROR;
      res.value = ref;
    }
    else
      res.code = UNKNOW_REF;
  }
  else if(req.action == "list")
  {
    string list = referencer.list_references();
    res.code = NO_ERROR;
    res.value = list;
  }
  else
    res.code = UNKNOW_ACTION;

  return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "reference_manager");

  ros::NodeHandle n;

  string service_name = "reference";
  if(argc > 1)
    service_name = argv[1];

  // Start up ROS service with callbacks
  ros::ServiceServer service = n.advertiseService(service_name, reference_handle);
  ROS_DEBUG("reference manager ready");

  ros::spin();

  ROS_DEBUG("KILL reference_manager");

  return 0;
}
