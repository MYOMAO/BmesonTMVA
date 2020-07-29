## Please Read the Following Instruction to Get Started ##

This repository is made to run TMVA package to apply machine learning on our newly process Bs and B+ CMS 2017 pp 5.02 TeV datasets in order to select optimal signal out from the background. If you successfully run the codes, you should be able to find the optimal working points for the B mesons, which will apply in our pp analysis

Some rename of the codes may need to be done since some of the codes' names are a little weird. Nonetheless, for the moment, let's stick to the names now and see if we can get the fits on the B mesons done.  

## To START ##

To get start, first clone the repository from github:

git clone https://github.com/MYOMAO/BmesonTMVA.git

Then go to the Bs folder by doing

cd Bs

Then do 

ls

You should see two folders

GetWorkingPoint	train


## TMVA Training ##

### Introduction ###


Briefly, TMVA stands for Toolkit for Multivariate Data Analysis with ROOT. It is a ROOT C++ framework to apply different machine learn algorithm to provide the users a new output variable V where V(v1,v2,v3,...,vn) and vn is the nth input variable that can significantly distinguish signal and background.


### Getting Familiar with the Codes ###


cd train

There are several important codes in the folder:

First have a look at TMVAClassification.C 

If you open TMVAClassification.C, you will find that there are different options for different training algorithms:

https://github.com/MYOMAO/BmesonTMVA/blob/master/Bs/train/TMVAClassification.C#L53-L116

From my experience, I beliebe CutSA, BDT, BDTG, and MLPBNN maybe useful. But you can try to play with some other algorithms.

You can customize your own algorithm in the shell script: run.TMVAClassification.sh

https://github.com/MYOMAO/BmesonTMVA/blob/master/Bs/train/run.TMVAClassification.sh#L28

I have alread enter the main variables list in the follow lines:

https://github.com/MYOMAO/BmesonTMVA/blob/master/Bs/train/run.TMVAClassification.sh#L47-L62

You can customize the training variables used in your TMVA training according to their IDs:

https://github.com/MYOMAO/BmesonTMVA/blob/master/Bs/train/run.TMVAClassification.sh#L41

Keep in mind that you can NEVER select Bmass, which is the variable we use to extract signal and background, as a training variable in the TMVA training. 


### Running TMVA on Bmesons ###


Now to run the TMVA on Bmesons, first copy the dataset name BsData.root and BsMC.root to a folder.

You can get them from my submit-hi2.mit.edu folder

Rename your input data path accordingly in 

https://github.com/MYOMAO/BmesonTMVA/blob/master/Bs/train/run.TMVAClassification.sh#L6-L7

Here, the sideband of the data is used as background and the gen matched candidates of the Bs decay is used as signal.

Then, run the shell script run.TMVAClassification.sh by:

source run.TMVAClassification.sh 1 1 5 10

Here 5 and 10 are the minimum and maximum pT bin in your training.

After running TMVA, it will take a long time for it to finish. Just get a coffee and wait until it finishes. 

After TMVA finishes, you can find the training output weight files at:

dataset/weights/rootfiles_TMVA_B_s_BDT_BDTG_5p0_10p0_0-1-2-3-4-5-6-7-8-9-10-11-12-13_root/TMVAClassification_BDT.class.C
dataset/weights/rootfiles_TMVA_B_s_BDT_BDTG_5p0_10p0_0-1-2-3-4-5-6-7-8-9-10-11-12-13_root/TMVAClassification_BDTG.class.C  
(The name inside weights depends on your set up, the default setup is BDT and BDTG training with pT 5 10 which gives us BDT_BDTG_5p0_10p0)

We will use them in the next stage

Also, you can check the results from the training such as the correlation matrices and the signal/background variable distribution under the folder:

dataset/plots/rootfiles_TMVA_B_s_BDT_BDTG_3p0_5p0_0-1-2-3-4-5-6-7-8-9-10-11-12-13_root/

We will procceed to the next step 



