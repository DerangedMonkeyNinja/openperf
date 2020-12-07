# coding: utf-8

"""
    OpenPerf API

    REST API interface for OpenPerf  # noqa: E501

    OpenAPI spec version: 1
    Contact: support@spirent.com
    Generated by: https://github.com/swagger-api/swagger-codegen.git
"""


import pprint
import re  # noqa: F401

import six


class CpuGeneratorCoreStats(object):
    """NOTE: This class is auto generated by the swagger code generator program.

    Do not edit the class manually.
    """

    """
    Attributes:
      swagger_types (dict): The key is attribute name
                            and the value is attribute type.
      attribute_map (dict): The key is attribute name
                            and the value is json key in definition.
    """
    swagger_types = {
        'available': 'int',
        'utilization': 'int',
        'target': 'int',
        'system': 'int',
        'user': 'int',
        'steal': 'int',
        'error': 'int',
        'targets': 'list[CpuGeneratorTargetStats]'
    }

    attribute_map = {
        'available': 'available',
        'utilization': 'utilization',
        'target': 'target',
        'system': 'system',
        'user': 'user',
        'steal': 'steal',
        'error': 'error',
        'targets': 'targets'
    }

    def __init__(self, available=None, utilization=None, target=None, system=None, user=None, steal=None, error=None, targets=None):  # noqa: E501
        """CpuGeneratorCoreStats - a model defined in Swagger"""  # noqa: E501

        self._available = None
        self._utilization = None
        self._target = None
        self._system = None
        self._user = None
        self._steal = None
        self._error = None
        self._targets = None
        self.discriminator = None

        self.available = available
        self.utilization = utilization
        self.target = target
        self.system = system
        self.user = user
        if steal is not None:
            self.steal = steal
        self.error = error
        self.targets = targets

    @property
    def available(self):
        """Gets the available of this CpuGeneratorCoreStats.  # noqa: E501

        The total amount of CPU time available  # noqa: E501

        :return: The available of this CpuGeneratorCoreStats.  # noqa: E501
        :rtype: int
        """
        return self._available

    @available.setter
    def available(self, available):
        """Sets the available of this CpuGeneratorCoreStats.

        The total amount of CPU time available  # noqa: E501

        :param available: The available of this CpuGeneratorCoreStats.  # noqa: E501
        :type: int
        """
        self._available = available

    @property
    def utilization(self):
        """Gets the utilization of this CpuGeneratorCoreStats.  # noqa: E501

        The amount of CPU time used  # noqa: E501

        :return: The utilization of this CpuGeneratorCoreStats.  # noqa: E501
        :rtype: int
        """
        return self._utilization

    @utilization.setter
    def utilization(self, utilization):
        """Sets the utilization of this CpuGeneratorCoreStats.

        The amount of CPU time used  # noqa: E501

        :param utilization: The utilization of this CpuGeneratorCoreStats.  # noqa: E501
        :type: int
        """
        self._utilization = utilization

    @property
    def target(self):
        """Gets the target of this CpuGeneratorCoreStats.  # noqa: E501

        The amount of target CPU time  # noqa: E501

        :return: The target of this CpuGeneratorCoreStats.  # noqa: E501
        :rtype: int
        """
        return self._target

    @target.setter
    def target(self, target):
        """Sets the target of this CpuGeneratorCoreStats.

        The amount of target CPU time  # noqa: E501

        :param target: The target of this CpuGeneratorCoreStats.  # noqa: E501
        :type: int
        """
        self._target = target

    @property
    def system(self):
        """Gets the system of this CpuGeneratorCoreStats.  # noqa: E501

        The amount of system time used, e.g. kernel or system calls  # noqa: E501

        :return: The system of this CpuGeneratorCoreStats.  # noqa: E501
        :rtype: int
        """
        return self._system

    @system.setter
    def system(self, system):
        """Sets the system of this CpuGeneratorCoreStats.

        The amount of system time used, e.g. kernel or system calls  # noqa: E501

        :param system: The system of this CpuGeneratorCoreStats.  # noqa: E501
        :type: int
        """
        self._system = system

    @property
    def user(self):
        """Gets the user of this CpuGeneratorCoreStats.  # noqa: E501

        The amount of user time used, e.g. openperf code  # noqa: E501

        :return: The user of this CpuGeneratorCoreStats.  # noqa: E501
        :rtype: int
        """
        return self._user

    @user.setter
    def user(self, user):
        """Sets the user of this CpuGeneratorCoreStats.

        The amount of user time used, e.g. openperf code  # noqa: E501

        :param user: The user of this CpuGeneratorCoreStats.  # noqa: E501
        :type: int
        """
        self._user = user

    @property
    def steal(self):
        """Gets the steal of this CpuGeneratorCoreStats.  # noqa: E501

        The amount of time the hypervisor reported our virtual cores were blocked  # noqa: E501

        :return: The steal of this CpuGeneratorCoreStats.  # noqa: E501
        :rtype: int
        """
        return self._steal

    @steal.setter
    def steal(self, steal):
        """Sets the steal of this CpuGeneratorCoreStats.

        The amount of time the hypervisor reported our virtual cores were blocked  # noqa: E501

        :param steal: The steal of this CpuGeneratorCoreStats.  # noqa: E501
        :type: int
        """
        self._steal = steal

    @property
    def error(self):
        """Gets the error of this CpuGeneratorCoreStats.  # noqa: E501

        The difference between intended and actual CPU utilization  # noqa: E501

        :return: The error of this CpuGeneratorCoreStats.  # noqa: E501
        :rtype: int
        """
        return self._error

    @error.setter
    def error(self, error):
        """Sets the error of this CpuGeneratorCoreStats.

        The difference between intended and actual CPU utilization  # noqa: E501

        :param error: The error of this CpuGeneratorCoreStats.  # noqa: E501
        :type: int
        """
        self._error = error

    @property
    def targets(self):
        """Gets the targets of this CpuGeneratorCoreStats.  # noqa: E501

        Statistics of the instruction sets (in the order they were specified in core configuration)  # noqa: E501

        :return: The targets of this CpuGeneratorCoreStats.  # noqa: E501
        :rtype: list[CpuGeneratorTargetStats]
        """
        return self._targets

    @targets.setter
    def targets(self, targets):
        """Sets the targets of this CpuGeneratorCoreStats.

        Statistics of the instruction sets (in the order they were specified in core configuration)  # noqa: E501

        :param targets: The targets of this CpuGeneratorCoreStats.  # noqa: E501
        :type: list[CpuGeneratorTargetStats]
        """
        self._targets = targets

    def to_dict(self):
        """Returns the model properties as a dict"""
        result = {}

        for attr, _ in six.iteritems(self.swagger_types):
            value = getattr(self, attr)
            if isinstance(value, list):
                result[attr] = list(map(
                    lambda x: x.to_dict() if hasattr(x, "to_dict") else x,
                    value
                ))
            elif hasattr(value, "to_dict"):
                result[attr] = value.to_dict()
            elif isinstance(value, dict):
                result[attr] = dict(map(
                    lambda item: (item[0], item[1].to_dict())
                    if hasattr(item[1], "to_dict") else item,
                    value.items()
                ))
            else:
                result[attr] = value
        if issubclass(CpuGeneratorCoreStats, dict):
            for key, value in self.items():
                result[key] = value

        return result

    def to_str(self):
        """Returns the string representation of the model"""
        return pprint.pformat(self.to_dict())

    def __repr__(self):
        """For `print` and `pprint`"""
        return self.to_str()

    def __eq__(self, other):
        """Returns true if both objects are equal"""
        if not isinstance(other, CpuGeneratorCoreStats):
            return False

        return self.__dict__ == other.__dict__

    def __ne__(self, other):
        """Returns true if both objects are not equal"""
        return not self == other
