import dataclasses, json

class EnhancedJSONEncoder(json.JSONEncoder):
        def default(self, o):
            if dataclasses.is_dataclass(o):
                return dataclasses.asdict(o)
            return super().default(o)

def serialize(foo: dataclasses.dataclass):
    return json.dumps(foo, cls=EnhancedJSONEncoder)

def deserialize(jdata: str) -> dataclasses.dataclass:
    return json.loads(jdata, cls=EnhancedJSONEncoder)