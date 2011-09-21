# This file contains a top-level script to run all of the Tcl
# tests.  Execute it by invoking "source all" when running tclTest
# in this directory.
#
# Copyright (c) 2000 Ajuba Solutions
# Copyright (c) 2003 Zveno Pty Ltd
#
# SCCS: @(#) all 1.8 97/08/01 11:07:14

package require Tcl 8.4
package require tcltest 2.2
tcltest::configure -testdir [file dirname [file normalize [info script]]]
eval tcltest::configure $argv
tcltest::runAllTests
