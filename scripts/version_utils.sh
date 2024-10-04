#!/bin/bash

get_version_from_json() {
  if [ -z "$1" ]; then
    jq -r '.version' library.json
  else
    git show "$1:library.json" | jq -r '.version'
  fi
}

get_version_from_properties() {
  if [ -z "$1" ]; then
    grep -E '^version=' library.properties | sed 's/version=//'
  else
    git show "$1:library.properties" | grep -E '^version=' | sed 's/version=//'
  fi
}

get_name_from_json() {
  jq -r '.name' library.json
}

get_name_from_properties() {
  grep -E '^name=' library.properties | sed 's/name=//'
}

get_dependencies_from_json() {
  jq -r '.dependencies | keys[]' library.json | sed 's|.*/||' | tr '\n' ',' | sed 's/,$//'
}

get_dependencies_from_properties() {
  grep -E '^depends=' library.properties | sed 's/depends=//' | tr -d ' ' | tr ',' '\n' | sort | tr '\n' ',' | sed 's/,$//'
}