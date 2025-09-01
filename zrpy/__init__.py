try:
    # 直接导入zrdds_python模块
    from . import zrdds_python
    # 将模块中的所有内容导入到当前命名空间
    globals().update(zrdds_python.__dict__)
except ImportError:
    # 如果相对导入失败，尝试绝对导入
    try:
        from zrpy import zrdds_python
        globals().update(zrdds_python.__dict__)
    except ImportError:
        # 如果都失败，提供有用的错误信息
        import sys
        import os
        print(f"导入错误：无法导入 zrdds_python 模块")
        print(f"当前工作目录：{os.getcwd()}")
        print(f"Python路径：{sys.path}")
        print("请确保：")
        print("1. 已正确安装包：pip install -e .")
        print("2. 或者从项目根目录运行：python -m zrpy")
        raise
