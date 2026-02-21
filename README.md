<h1>GIT MANAGER</h1>
<p>
##################################<br>
<h2><nospace>I N T R O D U C T I O N</h2>
##################################
<p>Git Manager is used to automatically initiate and maintain a local and a public repository, addressed by some paramenters given to the program<p>
##################################
<h2><nospace>U S A G E</h2>
##################################
<p>./git_manager init
<li>Enter gitHub user (What is the account name owning the repo)</li>
<li>Enter the project name (The name of the repo)</li>
<li>Enter the git repo username (Who is doing commits on local copy)</li>
<li>Enter the git repo email (Email of the person doing the commits on local copy)</li>
<li>This will initialize a brand new local repo and sync it to the GitHub origin</li>
<li>A tag v0.0.1 is associated to the first commit of the repo
<li>A README is automatically generated for every tag created
<hr>
<p>./git_manager "Commit String"
<li>This will go staging and committing the changes in the working directory</li>
<li>If on a branch rather than "main" it will checkout and merge to main
<hr>
<p>./git_manager "Commit String" [&nbsp;-t&nbsp;&nbsp;  -M&nbsp;|-m&nbsp;|-p&nbsp;&nbsp;]
<li>Commits changes in the working directory.</li>
<li>If run on a branch other than `main`, the tool will checkout and merge to `main`.</li>
<li>When `-t` is provided the tool also creates a tag against the last commit.</li>
<li>Tags follow `vM.m.p` format (e.g. `v1.2.1`). Use `-M` for major, `-m` for minor, `-p` for patch.</li>
<li>A `CURRENT` tag points to the last created tag. Creating a new minor release removes old non-current patch tags.</li>
<p>
<p>
###################################
<nospace><h2>C BUILD & USAGE</h2>
###################################
<p>
This repository includes C translations of the original shell scripts and a Makefile to build them.

- Files: See `git_manager.c`, `clean_tags.c`, `automatic_readme_generator.c`.
- Build: run `make` or build a single tool, for example:

```sh
make automatic_readme_generator
# or
gcc -O2 -Wall -o automatic_readme_generator automatic_readme_generator.c
```

- Notes:
	- The C programs shell out to `git` and expect POSIX tools (grep, awk) to be available.
	- On Windows use WSL, Git Bash, or MSYS2 to build and run the tools.
	- Built binaries are ignored by `.gitignore`; CI is recommended to produce release binaries if needed.

###################################
<nospace><h2>R E L E A S E&nbsp;&nbsp;&nbsp;N O T E S:</h2>
###################################<p>
<rlsnts>
<b><a href="https://github.com/GioLauria/git_manager/tree/v0.0.1">v0.0.1</a></b><br>-----------------------------<br>2586c65 Commit of 20201229 - 1609282505 -  REPO INIT
<br>-----------------------------<br><b><a href="https://github.com/GioLauria/git_manager/tree/v0.1.0">v0.1.0</a></b><br>-----------------------------<br><a href="https://github.com/GioLauria/git_manager/commit/ef76788">ef76788</a> #3 - Commit of 20201230 - 1609292264 - Fixed Rebase in lieu of a merge when current branch is not the main<br><a href="https://github.com/GioLauria/git_manager/commit/0fef551">0fef551</a> #2 - Commit of 20201230 - 1609282988 - Minor Formatting<br>-----------------------------<br><b><a href="https://github.com/GioLauria/git_manager/tree/v0.2.0">v0.2.0</a></b><br>-----------------------------<br><a href="https://github.com/GioLauria/git_manager/commit/1031319">1031319</a> #8 - Commit of 20201230 - 1609299287 - Fix: Syntax Error in code<br><a href="https://github.com/GioLauria/git_manager/commit/42bc950">42bc950</a> #7 - Commit of 20201230 - 1609299211 - Fix: Adding README generator caller on git_manager.sh<br><a href="https://github.com/GioLauria/git_manager/commit/8b1c893">8b1c893</a> #6 - Commit of 20201230 - 1609299151 - Fix: Adding README generator caller on git_manager.sh<br><a href="https://github.com/GioLauria/git_manager/commit/8ae5b5c">8ae5b5c</a> #5 - Commit of 20201230 - 1609299077 - Fix: Adding README generator caller on git_manager.sh<br><a href="https://github.com/GioLauria/git_manager/commit/ff0626d">ff0626d</a> #4 - Commit of 20201230 - 1609298875 - Feature: Adding a README generator<br>-----------------------------<br><b><a href="https://github.com/GioLauria/git_manager/tree/v0.3.0">v0.3.0</a></b><br>-----------------------------<br><a href="https://github.com/GioLauria/git_manager/commit/a47c8c7">a47c8c7</a> #36 - Commit of 20201230 - 1609308478 - Fixed README generator<br><a href="https://github.com/GioLauria/git_manager/commit/fcf1070">fcf1070</a> #35 - Commit of 20201230 - 1609305175 - Upload README file<br><a href="https://github.com/GioLauria/git_manager/commit/cd76005">cd76005</a> #34 - Commit of 20201230 - 1609305162 - Fixing README generator<br><a href="https://github.com/GioLauria/git_manager/commit/ebd305c">ebd305c</a> #33 - Commit of 20201230 - 1609305117 - Upload README file<br><a href="https://github.com/GioLauria/git_manager/commit/cffab68">cffab68</a> #32 - Commit of 20201230 - 1609305103 - Fixing README generator<br><a href="https://github.com/GioLauria/git_manager/commit/54f5b86">54f5b86</a> #31 - Commit of 20201230 - 1609304978 - Fixing README generator<br><a href="https://github.com/GioLauria/git_manager/commit/66826d2">66826d2</a> #30 - Commit of 20201230 - 1609304034 - Upload README file<br><a href="https://github.com/GioLauria/git_manager/commit/c97b346">c97b346</a> #29 - Commit of 20201230 - 1609304025 - Fixing README generator<br><a href="https://github.com/GioLauria/git_manager/commit/b439a16">b439a16</a> #28 - Commit of 20201230 - 1609303954 - Upload README file<br><a href="https://github.com/GioLauria/git_manager/commit/0556440">0556440</a> #27 - Commit of 20201230 - 1609303945 - Fixing README generator<br><a href="https://github.com/GioLauria/git_manager/commit/fae19e0">fae19e0</a> #26 - Commit of 20201230 - 1609303736 - Upload README file<br><a href="https://github.com/GioLauria/git_manager/commit/5b57d57">5b57d57</a> #24 - Commit of 20201230 - 1609302251 - Fixing README generator<br><a href="https://github.com/GioLauria/git_manager/commit/4b25ba6">4b25ba6</a> #23 - Commit of 20201230 - 1609302198 - Uploaded new README file<br><a href="https://github.com/GioLauria/git_manager/commit/1ec00ba">1ec00ba</a> #22 - Commit of 20201230 - 1609301486 - Feature: Reverse README Release notes<br><a href="https://github.com/GioLauria/git_manager/commit/94be327">94be327</a> #21 - Commit of 20201230 - 1609301379 - DUMMY patch<br><a href="https://github.com/GioLauria/git_manager/commit/c2c69dc">c2c69dc</a> #20 - Commit of 20201230 - 1609301302 - Test: Sleep time on generator<br><a href="https://github.com/GioLauria/git_manager/commit/e1d25cc">e1d25cc</a> #19 - Commit of 20201230 - 1609301251 - Upload README<br><a href="https://github.com/GioLauria/git_manager/commit/3424a2b">3424a2b</a> #18 - Commit of 20201230 - 1609301150 - Fix: Hide orphan commits<br><a href="https://github.com/GioLauria/git_manager/commit/9261345">9261345</a> #17 - Commit of 20201230 - 1609301023 - Removed garbage<br><a href="https://github.com/GioLauria/git_manager/commit/d9f4b80">d9f4b80</a> #16 - Commit of 20201230 - 1609300726 - Uploaded new README file<br><a href="https://github.com/GioLauria/git_manager/commit/d5fd75c">d5fd75c</a> #15 - Commit of 20201230 - 1609300601 - Fix: Added orphan commits to Release Notes<br><a href="https://github.com/GioLauria/git_manager/commit/8edc8f7">8edc8f7</a> #13 - Commit of 20201230 - 1609299653 - Fix: README generation issues<br><a href="https://github.com/GioLauria/git_manager/commit/fdef41f">fdef41f</a> #12 - Commit of 20201230 - 1609299538 - Fix: Removing Tags<br><a href="https://github.com/GioLauria/git_manager/commit/88aa78f">88aa78f</a> #11 - Commit of 20201230 - 1609299431 - Fix: README Errors<br><a href="https://github.com/GioLauria/git_manager/commit/8dc41eb">8dc41eb</a> #10 - Commit of 20201230 - 1609299397 - Fix: README Errors<br><a href="https://github.com/GioLauria/git_manager/commit/81d8398">81d8398</a> #9 - Commit of 20201230 - 1609299337 - Fix: Various Errors in generator<br>-----------------------------<br><b><a href="https://github.com/GioLauria/git_manager/tree/v0.4.0">v0.4.0</a></b><br>-----------------------------<br><a href="https://github.com/GioLauria/git_manager/commit/a1ee6c4">a1ee6c4</a> #47 - Commit of 20201230 - 1609312510 - Fixed README Gen<br><a href="https://github.com/GioLauria/git_manager/commit/bf72fba">bf72fba</a> #46 - Commit of 20201230 - 1609311880 - README<br><a href="https://github.com/GioLauria/git_manager/commit/bc08b40">bc08b40</a> #45 - Commit of 20201230 - 1609311852 - README<br><a href="https://github.com/GioLauria/git_manager/commit/245c9fe">245c9fe</a> #44 - Commit of 20201230 - 1609311787 - README<br><a href="https://github.com/GioLauria/git_manager/commit/41180cd">41180cd</a> #43 - Commit of 20201230 - 1609311753 - README<br><a href="https://github.com/GioLauria/git_manager/commit/b349cbb">b349cbb</a> #42 - Commit of 20201230 - 1609311685 - README<br><a href="https://github.com/GioLauria/git_manager/commit/f398def">f398def</a> #41 - Commit of 20201230 - 1609311652 - README<br><a href="https://github.com/GioLauria/git_manager/commit/d22bddd">d22bddd</a> #40 - Commit of 20201230 - 1609311620 - README<br><a href="https://github.com/GioLauria/git_manager/commit/4d8890e">4d8890e</a> #39 - Commit of 20201230 - 1609311582 - README<br><a href="https://github.com/GioLauria/git_manager/commit/7d5051b">7d5051b</a> #38 - Commit of 20201230 - 1609311561 - README<br><a href="https://github.com/GioLauria/git_manager/commit/bb14d8b">bb14d8b</a> #37 - Commit of 20201230 - 1609311535 - README<br><a href="https://github.com/GioLauria/git_manager/commit/bf680d6">bf680d6</a> #36 - Commit of 20201230 - 1609311418 - README<br><a href="https://github.com/GioLauria/git_manager/commit/2e01a23">2e01a23</a> #35 - Commit of 20201230 - 1609311318 - README<br><a href="https://github.com/GioLauria/git_manager/commit/c46b2f4">c46b2f4</a> #34 - Commit of 20201230 - 1609310792 - README<br><a href="https://github.com/GioLauria/git_manager/commit/a5d2c4d">a5d2c4d</a> #33 - Commit of 20201230 - 1609310775 - README<br><a href="https://github.com/GioLauria/git_manager/commit/56f8109">56f8109</a> #32 - Commit of 20201230 - 1609310679 - README<br><a href="https://github.com/GioLauria/git_manager/commit/d676e4b">d676e4b</a> #31 - Commit of 20201230 - 1609310626 - README<br><a href="https://github.com/GioLauria/git_manager/commit/41a61cc">41a61cc</a> #30 - Commit of 20201230 - 1609310567 - README<br><a href="https://github.com/GioLauria/git_manager/commit/152322d">152322d</a> #29 - Commit of 20201230 - 1609310523 - README<br><a href="https://github.com/GioLauria/git_manager/commit/6f571c7">6f571c