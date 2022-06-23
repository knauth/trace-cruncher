#!/bin/bash

# Script to download one or several git repos at a certain commit
# Takes inputs specified via command line or in a file
# Created by June Knauth (VMware) <june.knauth@gmail.com>, 2022-06-17

package=git-snapshot

download_checkout(){
  IN="${1}"
  # $fields=(${IN//;/ }) 
  IFS=';' read -ra ADDR <<< "$IN"
  
  git clone -b ${ADDR[2]} ${ADDR[1]} ${ADDR[0]}
  cd ${ADDR[0]}
  git checkout ${ADDR[3]} 
  cd .. 

  unset IFS
  # git clone -b ${fields[1]} ${fields[0]}
  # cd ${fields[0]}
  # git checkout ${fields[2]} 
  # cd ..
}

while test $# -gt 0; do
  case "$1" in
    -h|--help)
      echo "$package - Download a git repo and checkout a specific commit."
	  echo "Takes CLI and file arguments with format '<repo name>;<repo url>;<branch>;<commit hash>'"
      echo " "
      echo "$package [options] [arguments]"
      echo " "
      echo "options:"
      echo "-h, --help                show brief help"
      echo "-i, --input REPOS         specify a space-sep'd list of repos to download"
      echo "-f, --file FILE           specify an input file, one repo per line"
      exit 0
      ;;
    -i|--input)
      shift
      IFS=' ' 
      while read repo; do
        download_checkout $repo
      done <<< $1
      unset IFS
      break
      ;;
    -f|--file)
	  shift
      while read line; do
      download_checkout $line		
      done <$1
	  break
      ;;
    *)
      echo "Usage: ${package} [-s] [-i|--input] [-f|--file]"
      echo "${package} --help for more"
      break
      ;;
  esac
done

