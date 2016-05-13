#!/bin/bash

kill -SIGCONT $(ps aux | egrep '\./(principal)$' | awk '{print $2}')
