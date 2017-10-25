#! /bin/bash -ex

cd /home/ubuntu/github_repo/OpenIOLabs-Examples

cp -r /home/ubuntu/manual_builds/openio/src/scriptml/docs/c-api/* /home/ubuntu/github_repo/OpenIOLabs-Examples/documents/doxygen/c-api/.
cp -r /home/ubuntu/manual_builds/openio/src/scriptml/docs/python-api/* /home/ubuntu/github_repo/OpenIOLabs-Examples/documents/doxygen/python-api/.

env -i git config user.name jenkins-openiolabs
env -i git config user.email jenkins@openiolabs.co.uk

env -i git --git-dir=/home/ubuntu/github_repo/OpenIOLabs-Examples/.git --work-tree=/home/ubuntu/github_repo/OpenIOLabs-Examples pull



#env -i git pull


env -i git add /home/ubuntu/github_repo/OpenIOLabs-Examples/*

#OUTPUT="$(git commit -am 'Doxygen update')"
#echo "${OUTPUT}"

env -i OUTPUT="$(git commit -am 'Doxygen update')"
#env -i git remote set-url --push jenkins-openiolabs@github.com:openiolabs/OpenIOLabs-Examples.git
#env -i OUTPUT="$(git push jenkins-openiolabs@github.com:openiolabs/OpenIOLabs-Examples.git)"
#echo "${OUTPUT}"

env -i git push
