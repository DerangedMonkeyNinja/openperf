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


class InterfaceProtocolConfigIpv6(object):
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
        'method': 'str',
        'link_local_address': 'str',
        'static': 'InterfaceProtocolConfigIpv6Static',
        'dhcp6': 'InterfaceProtocolConfigIpv6Dhcp6'
    }

    attribute_map = {
        'method': 'method',
        'link_local_address': 'link_local_address',
        'static': 'static',
        'dhcp6': 'dhcp6'
    }

    def __init__(self, method=None, link_local_address=None, static=None, dhcp6=None):  # noqa: E501
        """InterfaceProtocolConfigIpv6 - a model defined in Swagger"""  # noqa: E501

        self._method = None
        self._link_local_address = None
        self._static = None
        self._dhcp6 = None
        self.discriminator = None

        self.method = method
        if link_local_address is not None:
            self.link_local_address = link_local_address
        if static is not None:
            self.static = static
        if dhcp6 is not None:
            self.dhcp6 = dhcp6

    @property
    def method(self):
        """Gets the method of this InterfaceProtocolConfigIpv6.  # noqa: E501

        Configuration method  # noqa: E501

        :return: The method of this InterfaceProtocolConfigIpv6.  # noqa: E501
        :rtype: str
        """
        return self._method

    @method.setter
    def method(self, method):
        """Sets the method of this InterfaceProtocolConfigIpv6.

        Configuration method  # noqa: E501

        :param method: The method of this InterfaceProtocolConfigIpv6.  # noqa: E501
        :type: str
        """
        self._method = method

    @property
    def link_local_address(self):
        """Gets the link_local_address of this InterfaceProtocolConfigIpv6.  # noqa: E501

        IPv6 link local address  # noqa: E501

        :return: The link_local_address of this InterfaceProtocolConfigIpv6.  # noqa: E501
        :rtype: str
        """
        return self._link_local_address

    @link_local_address.setter
    def link_local_address(self, link_local_address):
        """Sets the link_local_address of this InterfaceProtocolConfigIpv6.

        IPv6 link local address  # noqa: E501

        :param link_local_address: The link_local_address of this InterfaceProtocolConfigIpv6.  # noqa: E501
        :type: str
        """
        self._link_local_address = link_local_address

    @property
    def static(self):
        """Gets the static of this InterfaceProtocolConfigIpv6.  # noqa: E501


        :return: The static of this InterfaceProtocolConfigIpv6.  # noqa: E501
        :rtype: InterfaceProtocolConfigIpv6Static
        """
        return self._static

    @static.setter
    def static(self, static):
        """Sets the static of this InterfaceProtocolConfigIpv6.


        :param static: The static of this InterfaceProtocolConfigIpv6.  # noqa: E501
        :type: InterfaceProtocolConfigIpv6Static
        """
        self._static = static

    @property
    def dhcp6(self):
        """Gets the dhcp6 of this InterfaceProtocolConfigIpv6.  # noqa: E501


        :return: The dhcp6 of this InterfaceProtocolConfigIpv6.  # noqa: E501
        :rtype: InterfaceProtocolConfigIpv6Dhcp6
        """
        return self._dhcp6

    @dhcp6.setter
    def dhcp6(self, dhcp6):
        """Sets the dhcp6 of this InterfaceProtocolConfigIpv6.


        :param dhcp6: The dhcp6 of this InterfaceProtocolConfigIpv6.  # noqa: E501
        :type: InterfaceProtocolConfigIpv6Dhcp6
        """
        self._dhcp6 = dhcp6

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
        if issubclass(InterfaceProtocolConfigIpv6, dict):
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
        if not isinstance(other, InterfaceProtocolConfigIpv6):
            return False

        return self.__dict__ == other.__dict__

    def __ne__(self, other):
        """Returns true if both objects are not equal"""
        return not self == other
