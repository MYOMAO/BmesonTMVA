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



### Finding the Working Point For Maximum Statistical Significance ###


The next step is to find the working point for maximum significance. We first try that with rectangular cut. To do so, first open the folder

cd Bs/GetWorkingPoint/

Then do 

mkdir -p readxmlCut/plots

mkdir -p readxmlCut/weights

mkdir -p readxmlCut/results


Then transfer the .C and .xml file from the previous training to the weight folder:

cp ../train/dataset/weights/rootfiles_TMVA_B_s_BDT_BDTG_5p0_10p0_0-1-2-3-4-5-6-7-8-9-10-11-12-13_root/TMVAClassification_CutsSA.class.C  readxmlCut/weights

cp ../train/dataset/weights/rootfiles_TMVA_B_s_BDT_BDTG_5p0_10p0_0-1-2-3-4-5-6-7-8-9-10-11-12-13_root/TMVAClassification_CutsSA.weights.xml  readxmlCut/weights


Open the file RunTMVACUT.sh

Change the default setting 

ptmin=10

ptmax=15

to:

ptmin=5

ptmax=10


Then run the codes

source RunTMVACUT.sh

After the codes finish, you should see a table like below:

  ==========================================================
 |                         Opt Result                       |
  ----------------------------------------------------------
 | pT              | 10.0 - 15.0 GeV/c                      |
  ----------------------------------------------------------
 | RAA             | 1                                      |
  ----------------------------------------------------------
 | Sig reg         | +- 0.08   | Sideband bkg  | 29140      |
  ----------------------------------------------------------
 | weight S        | 367       | weight B      | 23312      |
  ----------------------------------------------------------
 | S               | 136       | B             | 1153       |
  ----------------------------------------------------------
 | effS            | 0.37      | sig           | 3.78       |
  ----------------------------------------------------------
 | CutsSA                              | 0                  |
  ==========================================================


  Now look up what you have on the effS column (Here is 0.37)


Then you open the xml file at

readxmlCut/weights/TMVAClassification_CutsSA.weights.xml

In the file, look for the signal efficiency =  0.37 

(Here we already pick the point with maximum statistical significance)

There are two options for optimization, the first one is the statistical significance (doNew = 0 in the codes readxml/readxml.cc). The second one is for the statistical significance with gamma quantile function (doNew = 1 in the codes readxml/readxml.cc). 

"<Bin ibin="38" effS="3.7000000000000000e-01" effB="4.9443759024143219e-02">"

Then look at the corresponding cuts on the efficiency. Here we have:

     <Cuts cutMin_0="1.3454600703877468e+00" cutMax_0="1.0000000000000000e+30" cutMin_1="1.9532580109462214e+00" cutMax_1="1.0000000000000000e+30" cutMin_2="-6.4620415769285415e+00" cutMax_2="1.0000000000000000e+30" cutMin_3="1.6199659529471382e+00" cutMax_3="1.0000000000000000e+30" cutMin_4="-1.0000000000000000e+30" cutMax_4="7.4112473423090336e+01" cutMin_5="-1.0000000000000000e+30" cutMax_5="7.7023538105115762e+01" cutMin_6="-1.0000000000000000e+30" cutMax_6="5.1479085447701236e-03" cutMin_7="-7.6865333225382972e+00" cutMax_7="1.0000000000000000e+30" cutMin_8="-1.0000000000000000e+30" cutMax_8="2.9174531245205273e+00" cutMin_9="8.3001511558650459e-02" cutMax_9="1.0000000000000000e+30"/>


For our training, we have already defined in the run.TMVAClassification.sh:


varlist=(
    '#  0  :  ("Btrk1Pt"  , "Btrk1Pt"                                                                                        , "FMax")  #' 
    '#  1  :  ("Btrk2Pt"  , "Btrk2Pt"                                                                                        , "FMin")  #' 
	'#  2  :  ("Trk1DCAz" , "Trk1DCAz := abs(Btrk1Dz1/Btrk1DzError1)"                                                                                       , "FMin")  #' 
	'#  3  :  ("Trk2DCAz" , "Trk2DCAz := abs(Btrk2Dz1/Btrk2DzError1)"                                                                                       , "FMin")  #' 
	'#  4  :  ("Trk1DCAxy"  , "Trk1DCAxy := abs(Btrk1Dxy1/Btrk1DxyError1)"                                                                 , "FMin")  #' 
	'#  5  :  ("Trk2DCAxy"  , "Trk2DCAxy := abs(Btrk2Dxy1/Btrk2DxyError1)"                                                                 , "FMin")  #' 
    '#  6  :  ("MassDis"  , "MassDis := abs(Btktkmass-1.019455)"                                                             , "FMax")  #' 
    '#  7  :  ("dls"      , "dls := BsvpvDistance/BsvpvDisErr"                                                                 , "FMax")  #' 
    '#  8  :  ("Balpha"   , "Balpha"                                                                                          , "FMax")  #' 
    '#  9  :  ("dls2D"    , "dls2D := Bd0"                                                                             , "FMin")  #' 
    '#  10 :  ("cos(Bdtheta)", "cos(Bdtheta)"                                                                                 , "FMax")  #' 
    '#  11 :  ("Bchi2cl",    "Bchi2cl"                                                                                             , ""    )  #'
	'#  12 :  ("Btrk1Eta", "Btrk1Eta"                                                                                 , "FMin")  #' 
	'#  13 :  ("Btrk2Eta", "Btrk2Eta"                                                                                 , "FMin")  #' 
)


So basically, we can apply the cut (min) as > and cut (max) < for the coresponding variable  in the dataset. 

1.0000000000000000e+30 means unbounded.

So now we have the (more or less) optimal cuts for the analysis! In the next step, we should apply the cut on the datasets and do the fits to really look at our optimal retangular cuts performance.


