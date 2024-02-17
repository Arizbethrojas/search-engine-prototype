# valid inputs
 ./querier ../common/output/letters-3 ../common/output/letters-3.index
echo "home"
#bad start to query 
 ./querier ../common/output/letters-3 ../common/output/letters-3.index
echo "and"

#invalid query 
 ./querier ../common/output/letters-3 ../common/output/letters-3.index
echo "23"
#invalid query 
 ./querier ../common/output/letters-3 ../common/output/letters-3.index
echo "??@?@?#?"