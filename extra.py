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

env.AddCustomTarget(
    name="build-interface",
    dependencies=None,
    actions=[
        "cd interface/ && yarn build",
        "rm -rf data/static/assets/",
        "mkdir -p data/static/ && cp -r interface/dist/* data/static/"
    ],
    title="Build react and copy it to data"
)
