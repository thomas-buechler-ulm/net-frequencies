include PATHS
###############################################
## BUILD
###############################################
OUR_MAIN = ./nf.x
$(OUR_MAIN): src
	  $(COMPILER) -I $(INC_DIR) -L $(LIB_DIR) \
	  src/main.cpp -o $(OUR_MAIN)  -ldivsufsort -ldivsufsort64 -O3 -DNDEBUG -march=native

###############################################
tiny: $(OUR_MAIN)
	mkdir -p data
	echo mississippi > data/mississippi
	#
	## NET FREQUENCIES
	$(OUR_MAIN) data/mississippi
	#
	## POSITIONS
	$(OUR_MAIN) data/mississippi -a

###############################################
## COMPARE CALCULATIONS
###############################################

run_compare_dna_nf: $(OUR_MAIN) $(GUO_MAIN) data/dna
	mkdir -p out
	$(TIME)                $(OUR_MAIN) data/dna -a   > out/dna.our.nf
	$(TIME) -o /dev/stdout $(GUO_MAIN) data/dna -a  2> out/dna.guo.nf
	sort -n out/dna.our.nf > out/dna.our.nf.sorted
	sort -n out/dna.guo.nf > out/dna.guo.nf.sorted
	echo DIFF:
	diff out/dna.our.nf.sorted out/dna.guo.nf.sorted

###############################################
## TIME MEASUREMENT
###############################################
run: run_no_out_dna run_no_out_proteins run_no_out_english

run_no_out_dna: $(OUR_MAIN) $(GUO_MAIN) data/dna
	mkdir -p out
	$(TIME) $(OUR_MAIN) data/dna     2> out/dna.no.our.log    > /dev/null
	$(TIME) $(OUR_MAIN) data/dna -a  2> out/dna.no.a.our.log  > /dev/null
	$(TIME) -o /dev/stdout $(GUO_MAIN) data/dna       > out/dna.no.guo.log   2> /dev/null
	$(TIME) -o /dev/stdout $(GUO_MAIN) data/dna   -a  > out/dna.no.a.guo.log 2> /dev/null

run_no_out_proteins: $(OUR_MAIN) $(GUO_MAIN) data/proteins
	mkdir -p out
	$(TIME) $(OUR_MAIN) data/proteins                     2> out/proteins.no.our.log    > /dev/null
	$(TIME) $(OUR_MAIN) data/proteins -a                  2> out/proteins.no.a.our.log  > /dev/null
	$(TIME) -o /dev/stdout $(GUO_MAIN) data/proteins       > out/proteins.no.guo.log   2> /dev/null
	$(TIME) -o /dev/stdout $(GUO_MAIN) data/proteins   -a  > out/proteins.no.a.guo.log 2> /dev/null

run_no_out_english: $(OUR_MAIN) $(GUO_MAIN) data/english.1024MB
	mkdir -p out
	$(TIME) $(OUR_MAIN) data/english.1024MB                     2> out/english.no.our.log    > /dev/null
	$(TIME) $(OUR_MAIN) data/english.1024MB -a                  2> out/english.no.a.our.log  > /dev/null
	$(TIME) -o /dev/stdout $(GUO_MAIN) data/english.1024MB       > out/english.no.guo.log   2> /dev/null
	$(TIME) -o /dev/stdout $(GUO_MAIN) data/english.1024MB   -a  > out/english.no.a.guo.log 2> /dev/null

###############################################
get_data:
	mkdir -p data
	wget https://pizzachili.dcc.uchile.cl/texts/nlang/english.1024MB.gz -P data
	wget https://pizzachili.dcc.uchile.cl/texts/protein/proteins.gz     -P data
	wget https://pizzachili.dcc.uchile.cl/texts/dna/dna.gz              -P data
	gunzip data/english.1024MB.gz
	gunzip data/proteins.gz
	gunzip data/dna.gz
	#replace NULL-BYTES in english
	awk '{ gsub(/\x00/, "\x01"); print }' data/english.1024MB > english.1024MB.1
	mv english.1024MB.1 data/english.1024MB

clean:
	rm -rf out
