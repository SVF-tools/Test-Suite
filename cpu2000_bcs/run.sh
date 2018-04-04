for f in `find . -name '*.orig'`; do
  echo $f 1>&2
  echo $f
  wpa -ander $f -print-pts
done
