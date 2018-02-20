#!/usr/bin/env bash
#TCB_Conversion_root $1_tcb_bin.root &
#for i in $(seq 1 28 )
#do
#    echo ${i}
#    #FADC_Conversion $1_fadc_${i}.dat 4 &
#    #FADC_Conversion_v1 $1_fadc_${i}.dat 4 &
#    FADC_Conversion_root $1_fadc_${i}_bin.root 4 &
#    #PEAK_Conversion $1_peak_${i}.dat &
#    echo $1_fadc_${i}.dat 4
#done 

TCBRawFilename=/mnt/SData0/TCBRawData/RUN_$1_tcb_bin.root
TCBConvFilename=/mnt/SData1/TCBConvData/RUN_$1_tcb_conv.root

nice -n 10 TCB_Conversion_root_v1 $TCBRawFilename $TCBConvFilename &
echo $TCBRawFilename
echo $TCBConvFilename

for i in $(seq 1 28)
do
    FADCRawFilename=""
    FADCConvFilename=""
    if [ $i -gt 0 ] && [ $i -le 7 ]
    then
	FADCRawFilename=/mnt/Data0/RawData/RUN_$1_fadc_${i}_bin.root
	FADCConvFilename=/mnt/Data0/ConvData/RUN_$1_fadc_${i}_conv.root
    elif [ $i -gt 7 ] && [ $i -le 14 ]
    then
	FADCRawFilename=/mnt/Data1/RawData/RUN_$1_fadc_${i}_bin.root
	FADCConvFilename=/mnt/Data1/ConvData/RUN_$1_fadc_${i}_conv.root	
    elif [ $i -gt 14 ] && [ $i -le 21 ]
    then
	FADCRawFilename=/mnt/Data2/RawData/RUN_$1_fadc_${i}_bin.root
	FADCConvFilename=/mnt/Data2/ConvData/RUN_$1_fadc_${i}_conv.root
    elif [ $i -gt 21 ] && [ $i -le 28 ]
    then
	FADCRawFilename=/mnt/Data3/RawData/RUN_$1_fadc_${i}_bin.root
	FADCConvFilename=/mnt/Data3/ConvData/RUN_$1_fadc_${i}_conv.root
    fi
    echo $FADCRawFilename
    echo $FADCConvFilename    
    nice -n 10 FADC_Conversion_root_v1 $FADCRawFilename $FADCConvFilename 4  ${1} &
done 

