rm -rf out.exe
rm -rf output.raw
rm -rf output2.png

dotnet run
ffmpeg -f rawvideo -pixel_format grayf32le -s 640x480 -i output.raw output2.png > /dev/null 2>&1