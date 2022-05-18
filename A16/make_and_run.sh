compiler="/Users/andreahuang/VulkanSDK/1.3.204.0/macOS/bin/glslc"

for f in ./shaders/*.frag
do
   $compiler $f -o  "${f%Shader.*}Frag.spv"
done

make clean
make
make test