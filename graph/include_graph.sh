#!/bin/sh

out=include.gv

cat > $out <<EOF
digraph G {
    graph [layout=dot rankdir=LR];
    label = "Include graph";
    overlap=false;
    splines=ortho;

    subgraph cluster_c {
        label = "";
        color = blue;
EOF

echo "$(find ../src/*.c -type f -printf '        "%f";\n')" >> $out
echo "    }" >> $out
echo >> $out
echo "    subgraph cluster_h {" >> $out
echo "        label = \"\"" >> $out
echo "        color = blue;" >> $out
echo "$(find ../src/*.h -type f -printf '        "%f";\n')" >> $out
echo "    }" >> $out
echo >> $out

for f in $(find ../src/*.* -type f) ; do
    echo -n "    \"$(find $f -printf '%f')\" -> { " >> $out
    grep "#include" $f | awk '{if (index($2, "<") == 0) {printf $2; printf " "}}' | >> $out
    echo '};' >> $out
done;

echo '}' >> $out
