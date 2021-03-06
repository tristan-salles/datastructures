% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/ds_map_multimap.R
\docType{class}
\name{multimap-class}
\alias{multimap-class}
\title{Multimap class}
\description{
Implementation of a multimap data structure, i.e. an unordered
collection of key-value pairs:
\deqn{f: keys -> values.}
Multimaps are able to store several identical keys. For a data structure
which unique keys, see \code{\link{hashmap}}.
Inserting and accessing is amortized in \emph{O(1)}.
\code{hashmap} wraps a C++ \code{unordered_multimap} using Rcpp modules.
Also see \code{\linkS4class{bimap}} for mappings in both ways.
}
\section{Slots}{

\describe{
\item{\code{.map}}{\code{C++} object representing a mapping}

\item{\code{.key.class}}{the class of the keys}
}}

\seealso{
\code{\link{multimap}} for creating a new \code{multimap} object
}
