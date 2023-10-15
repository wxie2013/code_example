purgelist -q > purge.list

readarray names < purge.list
for n in ${names[@]};do
  echo ${n}
  root -b -q ${n}
done

rm purge.list

