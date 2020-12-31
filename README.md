<h1>GIT MANAGER</h1>
<p>
##################################<br>
<h2><nospace>I N T R O D U C T I O N</h2>
##################################
<p>Git Manager is used to automatically initiate and maintain a local and a public repository, addressed by some paramenters given to the program<p>
##################################
<h2><nospace>U S A G E</h2>
##################################
<p>git_manager.sh init
<li>Enter gitHub user (What is the account name owning the repo)</li>
<li>Enter the project name (The name of the repo)</li>
<li>Enter the git repo username (Who is doing commits on local copy)</li>
<li>Enter the git repo email (Email of the person doing the commits on local copy)</li>
<li>This will initialize a brand new local repo and sync it to the GitHub origin</li>
<li>A tag v0.0.1 is associated to the first commit of the repo
<li>A README is automatically generated for every tag created
<hr>
<p>git_manager.sh "Commit String"
<li>This will go staging and committing the changes in the working directory</li>
<li>If on a branch rather than "main" it will checkout and merge to main
<hr>
<p>git_manager.sh "Commit String" [&nbsp;-t&nbsp;&nbsp;  -m&nbsp;|-n&nbsp;|-p&nbsp;&nbsp;]
<li>This will commit as before </li>
<li>The tag -t will also create a tag against the last commit</li>
<li>vM.m.p (v1.2.1)
<li>-M will increment the major version
<li>-m will increment the minor version
<li>-n will increment the minor version
<li>A "current" tag will be created pointing to the last tag created
<li>When creating a new minor release all patches tags of non current releases will be removed
<p>
<p>
###################################
<nospace><h2>R E L E A S E&nbsp;&nbsp;&nbsp;N O T E S:</h2>
###################################<p>
<rlsnts>
<b><a href="https://github.com/GioLauria/git_manager/tree/v0.0.1">v0.0.1</a></b> <br>----------------------------- <br>2586c65 Commit of 20201229 - 1609282505 -  REPO INIT <br>-----------------------------<br> <b><a href="https://github.com/GioLauria/git_manager/tree/v0.1.0">v0.1.0</a></b> <br>----------------------------- <br><a href="https://github.com/GioLauria/git_manager/commit/0fef551">0fef551</a> #2 - Commit of 20201230 - 1609282988 - Minor Formatting <br><a href="https://github.com/GioLauria/git_manager/commit/ef76788">ef76788</a> #3 - Commit of 20201230 - 1609292264 - Fixed Rebase in lieu of a merge when current branch is not the main <br>-----------------------------<br> <b><a href="https://github.com/GioLauria/git_manager/tree/v0.2.0">v0.2.0</a></b> <br>----------------------------- <br><a href="https://github.com/GioLauria/git_manager/commit/ff0626d">ff0626d</a> #4 - Commit of 20201230 - 1609298875 - Feature: Adding a README generator <br><a href="https://github.com/GioLauria/git_manager/commit/8ae5b5c">8ae5b5c</a> #5 - Commit of 20201230 - 1609299077 - Fix: Adding README generator caller on git_manager.sh <br><a href="https://github.com/GioLauria/git_manager/commit/8b1c893">8b1c893</a> #6 - Commit of 20201230 - 1609299151 - Fix: Adding README generator caller on git_manager.sh <br><a href="https://github.com/GioLauria/git_manager/commit/42bc950">42bc950</a> #7 - Commit of 20201230 - 1609299211 - Fix: Adding README generator caller on git_manager.sh <br><a href="https://github.com/GioLauria/git_manager/commit/1031319">1031319</a> #8 - Commit of 20201230 - 1609299287 - Fix: Syntax Error in code <br>-----------------------------<br> <b><a href="https://github.com/GioLauria/git_manager/tree/v0.3.0">v0.3.0</a></b> <br>----------------------------- <br><a href="https://github.com/GioLauria/git_manager/commit/81d8398">81d8398</a> #9 - Commit of 20201230 - 1609299337 - Fix: Various Errors in generator <br><a href="https://github.com/GioLauria/git_manager/commit/8dc41eb">8dc41eb</a> #10 - Commit of 20201230 - 1609299397 - Fix: README Errors <br><a href="https://github.com/GioLauria/git_manager/commit/88aa78f">88aa78f</a> #11 - Commit of 20201230 - 1609299431 - Fix: README Errors <br><a href="https://github.com/GioLauria/git_manager/commit/fdef41f">fdef41f</a> #12 - Commit of 20201230 - 1609299538 - Fix: Removing Tags <br><a href="https://github.com/GioLauria/git_manager/commit/8edc8f7">8edc8f7</a> #13 - Commit of 20201230 - 1609299653 - Fix: README generation issues <br><a href="https://github.com/GioLauria/git_manager/commit/d5fd75c">d5fd75c</a> #15 - Commit of 20201230 - 1609300601 - Fix: Added orphan commits to Release Notes <br><a href="https://github.com/GioLauria/git_manager/commit/d9f4b80">d9f4b80</a> #16 - Commit of 20201230 - 1609300726 - Uploaded new README file <br><a href="https://github.com/GioLauria/git_manager/commit/9261345">9261345</a> #17 - Commit of 20201230 - 1609301023 - Removed garbage <br><a href="https://github.com/GioLauria/git_manager/commit/3424a2b">3424a2b</a> #18 - Commit of 20201230 - 1609301150 - Fix: Hide orphan commits <br><a href="https://github.com/GioLauria/git_manager/commit/e1d25cc">e1d25cc</a> #19 - Commit of 20201230 - 1609301251 - Upload README <br><a href="https://github.com/GioLauria/git_manager/commit/c2c69dc">c2c69dc</a> #20 - Commit of 20201230 - 1609301302 - Test: Sleep time on generator <br><a href="https://github.com/GioLauria/git_manager/commit/94be327">94be327</a> #21 - Commit of 20201230 - 1609301379 - DUMMY patch <br><a href="https://github.com/GioLauria/git_manager/commit/1ec00ba">1ec00ba</a> #22 - Commit of 20201230 - 1609301486 - Feature: Reverse README Release notes <br><a href="https://github.com/GioLauria/git_manager/commit/4b25ba6">4b25ba6</a> #23 - Commit of 20201230 - 1609302198 - Uploaded new README file <br><a href="https://github.com/GioLauria/git_manager/commit/5b57d57">5b57d57</a> #24 - Commit of 20201230 - 1609302251 - Fixing README generator <br><a href="https://github.com/GioLauria/git_manager/commit/fae19e0">fae19e0</a> #26 - Commit of 20201230 - 1609303736 - Upload README file <br><a href="https://github.com/GioLauria/git_manager/commit/0556440">0556440</a> #27 - Commit of 20201230 - 1609303945 - Fixing README generator <br><a href="https://github.com/GioLauria/git_manager/commit/b439a16">b439a16</a> #28 - Commit of 20201230 - 1609303954 - Upload README file <br><a href="https://github.com/GioLauria/git_manager/commit/c97b346">c97b346</a> #29 - Commit of 20201230 - 1609304025 - Fixing README generator <br><a href="https://github.com/GioLauria/git_manager/commit/66826d2">66826d2</a> #30 - Commit of 20201230 - 1609304034 - Upload README file <br><a href="https://github.com/GioLauria/git_manager/commit/54f5b86">54f5b86</a> #31 - Commit of 20201230 - 1609304978 - Fixing README generator <br><a href="https://github.com/GioLauria/git_manager/commit/cffab68">cffab68</a> #32 - Commit of 20201230 - 1609305103 - Fixing README generator <br><a href="https://github.com/GioLauria/git_manager/commit/ebd305c">ebd305c</a> #33 - Commit of 20201230 - 1609305117 - Upload README file <br><a href="https://github.com/GioLauria/git_manager/commit/cd76005">cd76005</a> #34 - Commit of 20201230 - 1609305162 - Fixing README generator <br><a href="https://github.com/GioLauria/git_manager/commit/fcf1070">fcf1070</a> #35 - Commit of 20201230 - 1609305175 - Upload README file <br><a href="https://github.com/GioLauria/git_manager/commit/a47c8c7">a47c8c7</a> #36 - Commit of 20201230 - 1609308478 - Fixed README generator <br>-----------------------------<br> <b><a href="https://github.com/GioLauria/git_manager/tree/v0.4.0">v0.4.0</a></b> <br>----------------------------- <br><a href="https://github.com/GioLauria/git_manager/commit/611fb92">611fb92</a> #38 - Commit of 20201230 - 1609308652 - Cleaning <br><a href="https://github.com/GioLauria/git_manager/commit/278fdb8">278fdb8</a> #25 - Commit of 20201230 - 1609310146 - Fixing README <br><a href="https://github.com/GioLauria/git_manager/commit/eca82da">eca82da</a> #26 - Commit of 20201230 - 1609310182 - README <br><a href="https://github.com/GioLauria/git_manager/commit/4a795b0">4a795b0</a> #27 - Commit of 20201230 - 1609310458 - README <br><a href="https://github.com/GioLauria/git_manager/commit/6f571c7">6f571c7</a> #28 - Commit of 20201230 - 1609310485 - README <br><a href="https://github.com/GioLauria/git_manager/commit/152322d">152322d</a> #29 - Commit of 20201230 - 1609310523 - README <br><a href="https://github.com/GioLauria/git_manager/commit/41a61cc">41a61cc</a> #30 - Commit of 20201230 - 1609310567 - README <br><a href="https://github.com/GioLauria/git_manager/commit/d676e4b">d676e4b</a> #31 - Commit of 20201230 - 1609310626 - README <br><a href="https://github.com/GioLauria/git_manager/commit/56f8109">56f8109</a> #32 - Commit of 20201230 - 1609310679 - README <br><a href="https://github.com/GioLauria/git_manager/commit/a5d2c4d">a5d2c4d</a> #33 - Commit of 20201230 - 1609310775 - README <br><a href="https://github.com/GioLauria/git_manager/commit/c46b2f4">c46b2f4</a> #34 - Commit of 20201230 - 1609310792 - README <br><a href="https://github.com/GioLauria/git_manager/commit/2e01a23">2e01a23</a> #35 - Commit of 20201230 - 1609311318 - README <br><a href="https://github.com/GioLauria/git_manager/commit/bf680d6">bf680d6</a> #36 - Commit of 20201230 - 1609311418 - README <br><a href="https://github.com/GioLauria/git_manager/commit/bb14d8b">bb14d8b</a> #37 - Commit of 20201230 - 1609311535 - README <br><a href="https://github.com/GioLauria/git_manager/commit/7d5051b">7d5051b</a> #38 - Commit of 20201230 - 1609311561 - README <br><a href="https://github.com/GioLauria/git_manager/commit/4d8890e">4d8890e</a> #39 - Commit of 20201230 - 1609311582 - README <br><a href="https://github.com/GioLauria/git_manager/commit/d22bddd">d22bddd</a> #40 - Commit of 20201230 - 1609311620 - README <br><a href="https://github.com/GioLauria/git_manager/commit/f398def">f398def</a> #41 - Commit of 20201230 - 1609311652 - README <br><a href="https://github.com/GioLauria/git_manager/commit/b349cbb">b349cbb</a> #42 - Commit of 20201230 - 1609311685 - README <br><a href="https://github.com/GioLauria/git_manager/commit/41180cd">41180cd</a> #43 - Commit of 20201230 - 1609311753 - README <br><a href="https://github.com/GioLauria/git_manager/commit/245c9fe">245c9fe</a> #44 - Commit of 20201230 - 1609311787 - README <br><a href="https://github.com/GioLauria/git_manager/commit/bc08b40">bc08b40</a> #45 - Commit of 20201230 - 1609311852 - README <br><a href="https://github.com/GioLauria/git_manager/commit/bf72fba">bf72fba</a> #46 - Commit of 20201230 - 1609311880 - README <br><a href="https://github.com/GioLauria/git_manager/commit/a1ee6c4">a1ee6c4</a> #47 - Commit of 20201230 - 1609312510 - Fixed README Gen <br>-----------------------------<br> <b><a href="https://github.com/GioLauria/git_manager/tree/v0.5.0">v0.5.0</a></b> <br>----------------------------- <br><a href="https://github.com/GioLauria/git_manager/commit/d2ab3a8">d2ab3a8</a> #22 - Commit of 20201230 - 1609301486 - Feature: Reverse README Release notes <br><a href="https://github.com/GioLauria/git_manager/commit/6279722">6279722</a> #23 - Commit of 20201230 - 1609340402 - Line 43 generator. Echoing values of a variable instead of assigning it <br><a href="https://github.com/GioLauria/git_manager/commit/b378afb">b378afb</a> #24 - Commit of 20201230 - 1609340470 - Initialize variables on generator <br><a href="https://github.com/GioLauria/git_manager/commit/1763cae">1763cae</a> #26 - Commit of 20201230 - 1609342205 - Minor edits on manager <br><a href="https://github.com/GioLauria/git_manager/commit/93ac3a8">93ac3a8</a> #27 - Commit of 20201230 - 1609342347 - Feature: Adding tag CURRENT to last tag created <br>-----------------------------<br> <b><a href="https://github.com/GioLauria/git_manager/tree/v0.6.0">v0.6.0</a></b> <br>----------------------------- <br><a href="https://github.com/GioLauria/git_manager/commit/8f74ae1">8f74ae1</a> #30 - Commit of 20201230 - 1609348640 - Feature: Integratig Tag Cleaning Procedure <br>-----------------------------<br> <b><a href="https://github.com/GioLauria/git_manager/tree/v0.7.0">v0.7.0</a></b> <br>----------------------------- <br><a href="https://github.com/GioLauria/git_manager/commit/3c8f251">3c8f251</a> #31 - Commit of 20201230 - 1609348744 - Uploaded README <br><a href="https://github.com/GioLauria/git_manager/commit/2326a6c">2326a6c</a> #33 - Commit of 20201230 - 1609348979 - Minor fixes on cleaner <br><a href="https://github.com/GioLauria/git_manager/commit/dee3157">dee3157</a> #34 - Commit of 20201230 - 1609349021 - Uploading README <br><a href="https://github.com/GioLauria/git_manager/commit/516ec8b">516ec8b</a> #35 - Commit of 20201230 - 1609349100 - Cleaner run <br><a href="https://github.com/GioLauria/git_manager/commit/63de1a6">63de1a6</a> #36 - Commit of 20201230 - 1609349465 - Fix Remote Tagging Removal <br>-----------------------------<br> <b><a href="https://github.com/GioLauria/git_manager/tree/v0.8.0">v0.8.0</a></b> <br>----------------------------- <br><a href="https://github.com/GioLauria/git_manager/commit/57e810b">57e810b</a> #37 - Commit of 20201230 - 1609349542 - Fix Remote Tagging Removal <br><a href="https://github.com/GioLauria/git_manager/commit/4cdb3f2">4cdb3f2</a> #38 - Commit of 20201230 - 1609349641 - Upload README <br><a href="https://github.com/GioLauria/git_manager/commit/37357fa">37357fa</a> #39 - Commit of 20201230 - 1609349914 - Minor Changes on generator <br><a href="https://github.com/GioLauria/git_manager/commit/0b2ba97">0b2ba97</a> #40 - Commit of 20201230 - 1609350030 - Upload README <br><a href="https://github.com/GioLauria/git_manager/commit/69087f3">69087f3</a> #41 - Commit of 20201231 - 1609369727 - Upload README <br><a href="https://github.com/GioLauria/git_manager/commit/0bc3ed2">0bc3ed2</a> #42 - Commit of 20201231 - 1609373058 - Moved Creation of README and Tag Cleaning only if a new tag is being created
