rm -rf out.exe
rm -rf output.raw
rm -rf output2.png

make
result=$(./out.exe $1 $2 $3)
echo $result > output.csv
ffmpeg -f rawvideo -pixel_format grayf32le -s 640x480 -i output.raw output2.png > /dev/null 2>&1