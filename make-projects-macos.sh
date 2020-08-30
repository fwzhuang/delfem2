echo "#################################"
echo "download & build submodules"
echo "#################################"

git submodule update --init --recursive

echo "################################"
echo "build examples_glfwnew"
echo "################################"

cd 3rd_party/glfw
cmake .
make
cd ../..

cd examples_glfwnew
mkdir buildXcodeHdronly
cd buildXcodeHdronly
cmake -G Xcode -DUSE_HEADERONLY=ON ..
cmake --build .
cd ../../

cd examples_glfwnew
mkdir buildXcodeStatic
cd buildXcodeStatic
cmake -G Xcode -DUSE_HEADERONLY=OFF ..
cmake --build .
cd ../../

cd examples_glfwnew
mkdir buildEm
cd buildEm
cmake -DEMSCRIPTEN=ON -DUSE_HEADERONLY=ON ..
make
cd ../../


echo "################################"
echo "build examples_glfwold"
echo "################################"

cd examples_glfwold
mkdir buildXcodeHdronly
cd buildXcodeHdronly
cmake -G Xcode -DUSE_HEADERONLY=ON ..
# cmake --build . # skip build to save time
cd ../../

cd examples_glfwold
mkdir buildXcodeStatic
cd buildXcodeStatic
cmake -G Xcode -DUSE_HEADERONLY=OFF ..
# cmake --build . # skip build to save time
cd ../../

cd examples_glfwold
mkdir buildMakeHdronly 
cd buildMakeHdronly
cmake -DUSE_HEADERONLY=ON ..
make
cd ../../

cd examples_glfwold
mkdir buildMakeStatic 
cd buildMakeStatic
cmake -DUSE_HEADERONLY=OFF ..
make
cd ../../


echo "################################"
echo "build examples_smpl"
echo "################################"

cd examples_smpl
mkdir buildXcodeHdronly
cd buildXcodeHdronly
cmake -G Xcode -DUSE_HEADERONLY=ON ..
# cmake --build . # skip build to save time
cd ../../


echo "################################"
echo "build examples_glut"
echo "################################"

cd examples_glut
mkdir buildMake
cd buildMake
cmake ..
make
cd ../../

cd examples_glut
mkdir buildXcode
cd buildXcode
cmake -G Xcode ..
cmake --build .
cd ../../


##################################
## build CSharp

#cd src_dll 
#mkdir build 
#cd build
#cmake ..
#make
#cd ../../

#cd examples_cs
#mcs helloworld.cs -define:__APPLE__ -out:helloworld.exe
#mono helloworld.exe
#./helloworld.exe
#cd ../

################################
# build python

#virtualenv --python=python3.7 myenv
#PATH_PYTHON="myenv/bin/"
#PATH_PYTHON=$( cd ${PATH_PYTHON}; pwd )"/python3"
PATH_PYTHON=$(which python)
echo ${PATH_PYTHON}

cd src_pybind/core
mkdir buildXcode 
cd buildXcode
cmake -G Xcode -DPYTHON_EXECUTABLE:PATH=${PATH_PYTHON}  ..
cd ../../../

cd src_pybind/gl
mkdir buildXcode 
cd buildXcode
cmake -G Xcode -DPYTHON_EXECUTABLE:PATH=${PATH_PYTHON}  ..
cd ../../../

pip3 uninstall PyDelFEM2 -y
pip3 uninstall PyDelFEM2 -y
pip3 install -e .

pip3 install -U pytest
pytest -s 
#python3 setup.py install
#python3 setup.py test
#python3 setup.py sdist bdist_wheel
#twine upload dist/*


echo "###############################"
echo "test cpp"
echo "###############################"
# (this takes time so put it in the end)

cd "3rd_party/googletest"
cmake .
make
cd ../../

cd test_cpp
mkdir buildXcodeStatic
cd buildXcodeStatic
cmake -G Xcode -DUSE_HEADERONLY=OFF ..
cd ../../

cd test_cpp
mkdir buildXcodeHdronly
cd buildXcodeHdronly
cmake -G Xcode -DUSE_HEADERONLY=ON ..
cd ../../

cd test_cpp
mkdir buildMakeHdronly
cd buildMakeHdronly
cmake -DUSE_HEADERONLY=ON ..
make
cd ../../

cd test_cpp
mkdir buildMakeStatic
cd buildMakeStatic
cmake -DUSE_HEADERONLY=OFF ..
make
./runUnitTests
cd ../../

#################################
# torch extension

pip3 uninstall torch_delfem2 -y
pip3 install torch
cd src_pybind/torch
python3 setup.py develop
cd ../../


################################
# SMPL
pip3 install chumpy
cd test_inputs
python3 smpl_preprocess.py 
pip3 uninstall chumpy -y


