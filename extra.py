Import("env")
env.Replace(COMPILATIONDB_INCLUDE_TOOLCHAIN=True)

env.AddCustomTarget(
    name="ctags",
    dependencies=None,
    actions=[
        "ctags -R ${PROJECT_SRC_DIR} ${PROJECT_INCLUDE_DIR} ${PROJECT_LIBDEPS_DIR}"
    ],
    title="Generated tags file"
)
