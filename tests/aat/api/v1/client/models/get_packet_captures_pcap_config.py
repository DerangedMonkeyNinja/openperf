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


class GetPacketCapturesPcapConfig(object):
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
        'ids': 'list[str]',
        'packet_start': 'int',
        'packet_end': 'int'
    }

    attribute_map = {
        'ids': 'ids',
        'packet_start': 'packet_start',
        'packet_end': 'packet_end'
    }

    def __init__(self, ids=None, packet_start=None, packet_end=None):  # noqa: E501
        """GetPacketCapturesPcapConfig - a model defined in Swagger"""  # noqa: E501

        self._ids = None
        self._packet_start = None
        self._packet_end = None
        self.discriminator = None

        self.ids = ids
        if packet_start is not None:
            self.packet_start = packet_start
        if packet_end is not None:
            self.packet_end = packet_end

    @property
    def ids(self):
        """Gets the ids of this GetPacketCapturesPcapConfig.  # noqa: E501

        List of capture results identifiers  # noqa: E501

        :return: The ids of this GetPacketCapturesPcapConfig.  # noqa: E501
        :rtype: list[str]
        """
        return self._ids

    @ids.setter
    def ids(self, ids):
        """Sets the ids of this GetPacketCapturesPcapConfig.

        List of capture results identifiers  # noqa: E501

        :param ids: The ids of this GetPacketCapturesPcapConfig.  # noqa: E501
        :type: list[str]
        """
        self._ids = ids

    @property
    def packet_start(self):
        """Gets the packet_start of this GetPacketCapturesPcapConfig.  # noqa: E501

        The packet offset in the capture buffer to start reading (0 based)  # noqa: E501

        :return: The packet_start of this GetPacketCapturesPcapConfig.  # noqa: E501
        :rtype: int
        """
        return self._packet_start

    @packet_start.setter
    def packet_start(self, packet_start):
        """Sets the packet_start of this GetPacketCapturesPcapConfig.

        The packet offset in the capture buffer to start reading (0 based)  # noqa: E501

        :param packet_start: The packet_start of this GetPacketCapturesPcapConfig.  # noqa: E501
        :type: int
        """
        self._packet_start = packet_start

    @property
    def packet_end(self):
        """Gets the packet_end of this GetPacketCapturesPcapConfig.  # noqa: E501

        The packet offset in the capture buffer to end reading (0 based)  # noqa: E501

        :return: The packet_end of this GetPacketCapturesPcapConfig.  # noqa: E501
        :rtype: int
        """
        return self._packet_end

    @packet_end.setter
    def packet_end(self, packet_end):
        """Sets the packet_end of this GetPacketCapturesPcapConfig.

        The packet offset in the capture buffer to end reading (0 based)  # noqa: E501

        :param packet_end: The packet_end of this GetPacketCapturesPcapConfig.  # noqa: E501
        :type: int
        """
        self._packet_end = packet_end

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
        if issubclass(GetPacketCapturesPcapConfig, dict):
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
        if not isinstance(other, GetPacketCapturesPcapConfig):
            return False

        return self.__dict__ == other.__dict__

    def __ne__(self, other):
        """Returns true if both objects are not equal"""
        return not self == other