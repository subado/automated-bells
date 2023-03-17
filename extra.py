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
    name="build-react",
    dependencies=None,
    actions=[
        "cd interface/ && yarn build",
        "rm -rf data/assets/",
        "mkdir -p data/ && cp -r interface/dist/* data/"
    ],
    title="Build react and copy it to data"
)
