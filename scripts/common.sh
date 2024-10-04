#!/bin/bash

get_version_from_json() {
  jq -r '.version' library.json
}

get_version_from_properties() {
  grep -E '^version=' library.properties | sed 's/version=//'
}

get_name_from_json() {
  jq -r '.name' library.json
}

get_name_from_properties() {
  grep -E '^name=' library.properties | sed 's/name=//'
}

get_dependencies_from_json() {
  jq -r '.dependencies | keys[]' library.json | tr '\n' ',' | sed 's/,$//'
}

get_dependencies_from_properties() {
  grep -E '^depends=' library.properties | sed 's/depends=//' | tr -d ' ' | tr ',' '\n' | sort | tr '\n' ',' | sed 's/,$//'
}