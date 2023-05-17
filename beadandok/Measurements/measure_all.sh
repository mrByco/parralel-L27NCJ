

radius=(1 2 3 5 7 10 20)
threads=(1 2 3 5 7 15 35 55 100)

echo "r,t,firstResult,secondResult,thirdResult" > output.csv

for t in "${threads[@]}"; do
    for r in "${radius[@]}"; do
        firstResult=$(./1.exe "$r" "$t")
        secondResult=$(./2.exe "$r" "$t")
        thirdResult=$(./net6.0/GuassianBlur.exe "$r" "$t")
        echo "$r,$t,$firstResult,$secondResult,$thirdResult" >> output.csv
    done
done