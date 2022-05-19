compiler="/Users/andreahuang/VulkanSDK/1.3.204.0/macOS/bin/glslc"

for f in ./shaders/*.frag
do
   $compiler $f -o  "${f%Shader.*}Frag.spv"
done

for f in ./shaders/*.vert
do
   $compiler $f -o "${f%Shader.*}Vert.spv"
done

make clean
make
make test