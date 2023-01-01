from dataclasses import dataclass

from utils.serialize_dataclass import serialize, deserialize

from code_generation.cpp_generator import CppClass, CppArray, CppVariable, CppEnum

@dataclass
class AdcSettings:
    """Class that outlines the settings of a peripheral adc."""

class AdcBase:
    def __init__(self, json_settings: str):
        self.settings = AdcSettings
        self.settings = deserialize(json_settings)