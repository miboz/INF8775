density=0.9


for nbNodes in $(seq 939 1 1000)
do
  for seed in $(seq 0 1 9)
  do
    echo "0 ${seed} 1 ${nbNodes} 1 ${density}" | ./bin/generator ../instances/"${nbNodes}_${seed}"
  done
done