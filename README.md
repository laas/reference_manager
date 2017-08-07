# <img src="logo/referencer.png" width="100"> reference_manager
This repository is a ROS package to handle references between multiple nodes

## Installation

To install this, put it in your catkin workspace:

```
$ cd ~/catkin_ws/src/

$ git clone https://github.com/sarthou/reference_manager.git

$ cd ..

$ catkin_make
```

## Run the node

You have two way to run this node :

You can run it with the default service name *reference*
```
rosrun reference_manager referencer
```

But you can also choose the service name with :
```
rosrun reference_manager referencer my_referencer
```

> Renaming the service can be useful if you need multiple references manager at the same time

## Usage

> In the examples below, we assume that the service has been renamed *my_referencer*

- Add a new referencer
```
rosservice call /my_referencer "{param: 'an_identifier:its_reference', action: 'reference'}"
```

> Note that the identifier and its corresponding reference are separated by **:**

- Test if an identifier is referenced
```
rosservice call /my_referencer "{param: '', action: 'list'}"
```

- Get the identifier from its reference
```
rosservice call /my_referencer "{param: 'its_reference', action: 'get_id'}"
```

- Get the reference from an identifier
```
rosservice call /my_referencer "{param: 'an_identifier', action: 'get_ref'}"
```

- List all references and their corresponding identifier
```
rosservice call /my_referencer "{param: '', action: 'list'}"
```

- Remove a reference
```
rosservice call /my_referencer "{param: 'its_reference', action: 'unreference'}"
```

## Error codes

This service returns an error code explaining what happened.
All codes are as follows:

Error name      | Error code
-------------   | -------------
NO_ERROR        | 0
UNKNOW_ACTION   | 2
UNREFERENCED_ID | 3
REF_ALREADY_USED| 4
UNKNOW_REF      | 6
OTHER           | 8
