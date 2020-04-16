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


class MemoryGenerator(object):
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
        'id': 'str',
        'config': 'MemoryGeneratorConfig',
        'running': 'bool'
    }

    attribute_map = {
        'id': 'id',
        'config': 'config',
        'running': 'running'
    }

    def __init__(self, id=None, config=None, running=None):  # noqa: E501
        """MemoryGenerator - a model defined in Swagger"""  # noqa: E501

        self._id = None
        self._config = None
        self._running = None
        self.discriminator = None

        self.id = id
        self.config = config
        self.running = running

    @property
    def id(self):
        """Gets the id of this MemoryGenerator.  # noqa: E501

        Unique memory generator identifier  # noqa: E501

        :return: The id of this MemoryGenerator.  # noqa: E501
        :rtype: str
        """
        return self._id

    @id.setter
    def id(self, id):
        """Sets the id of this MemoryGenerator.

        Unique memory generator identifier  # noqa: E501

        :param id: The id of this MemoryGenerator.  # noqa: E501
        :type: str
        """
        self._id = id

    @property
    def config(self):
        """Gets the config of this MemoryGenerator.  # noqa: E501


        :return: The config of this MemoryGenerator.  # noqa: E501
        :rtype: MemoryGeneratorConfig
        """
        return self._config

    @config.setter
    def config(self, config):
        """Sets the config of this MemoryGenerator.


        :param config: The config of this MemoryGenerator.  # noqa: E501
        :type: MemoryGeneratorConfig
        """
        self._config = config

    @property
    def running(self):
        """Gets the running of this MemoryGenerator.  # noqa: E501

        Indicates whether this generator is currently running.  # noqa: E501

        :return: The running of this MemoryGenerator.  # noqa: E501
        :rtype: bool
        """
        return self._running

    @running.setter
    def running(self, running):
        """Sets the running of this MemoryGenerator.

        Indicates whether this generator is currently running.  # noqa: E501

        :param running: The running of this MemoryGenerator.  # noqa: E501
        :type: bool
        """
        self._running = running

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
        if issubclass(MemoryGenerator, dict):
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
        if not isinstance(other, MemoryGenerator):
            return False

        return self.__dict__ == other.__dict__

    def __ne__(self, other):
        """Returns true if both objects are not equal"""
        return not self == other
