$dir = Get-ChildItem -Directory -exclude install

$config = @("Debug", "Release", "RelWithDebInfo")

foreach ($d in $dir) {
    foreach ($c in $config) {
        cmake -S $d -B $d/build -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX="install/$c"
        cmake --build $d/build --config $c --target install
    }
    Remove-Item $d/build -Force
}