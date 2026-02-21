import sys
try:
    import yaml
except Exception:
    print('PYYAML_MISSING')
    sys.exit(2)
try:
    with open('.github/workflows/build.yml','r',encoding='utf-8') as f:
        data = yaml.safe_load(f)
    print('YAML_OK')
except Exception as e:
    print('YAML_ERROR')
    print(e)
    sys.exit(1)
