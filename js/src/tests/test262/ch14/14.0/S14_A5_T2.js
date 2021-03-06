// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * The Identifer within a FunctionDeclaration can be written in both letters and unicode
 *
 * @path ch14/14.0/S14_A5_T2.js
 * @description Declaring a function with "function \u005f\u005f\u0066\u0075\u006e\u0063(){return "unicode"}"
 */

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__func() !== "unicode") {
	$ERROR('#1: __func() === "unicode". Actual:  __func() ==='+ __func()  );
}
//
//////////////////////////////////////////////////////////////////////////////

function __func(){return "ascii"};
function \u005f\u005f\u0066\u0075\u006e\u0063(){return "unicode"};//__func in unicode

