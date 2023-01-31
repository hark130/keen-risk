# keen-risk

KEEN RISK (KERI) - C Programming course material delivered by slides-as-code.

## Description

KERI was created to aid in the revision and formatting of C programming training material.
KERI was named in honor of [KErnighan](https://en.wikipedia.org/wiki/Brian_Kernighan) and [RItchie](https://en.wikipedia.org/wiki/Dennis_Ritchie), without whom the landscape of our global society would be surprisingly unfamiliar.  Additionally, I believe the phrase "keen risk" is a vaguely accurate description of the C programming languge.

## Dependencies

To build and archive the slides from their raw `.rst` format using this repository's makefile, independent of host operating system, you will need the following:

* Ruby
* Ruby Gems
* Python3
* Hovercraft
* Bourbon
* GNU Make

See: Installation

## Repository Structure

* `LICENSE`: Repository license file.
* `README.md`: This file.
* `slides_raw`: Directory containing raw `.rst` "source" files.
* `slides_build`: Directory containing HTML pages "compiled" from the raw `.rst` "source" files.
* `slides_archive`: Directory containing zip-formatted archive files containing the "compiled" HTML pages.

## Installation

1. [Ruby](https://www.ruby-lang.org/en/documentation/installation/)
2. [Ruby Gems](https://rubygems.org/): "Ruby 1.9 and newer ships with RubyGems built-in but you may need to upgrade for bug fixes or new features. To upgrade RubyGems, visit the [download](https://rubygems.org/pages/download) page."
3. [Python3](https://www.python.org/downloads/)
4. [Hovercraft](https://github.com/regebro/hovercraft#installation)
5. [Bourbon](https://github.com/thoughtbot/bourbon#installation)
6. [GNU Make](https://www.gnu.org/software/make/)
    * Linux
        * Consider using your package manager (e.g., `apt install build-essential`) -or-
        * [Download](https://www.gnu.org/software/make/#download) and install manually
    * Windows
        * [Download](https://gnuwin32.sourceforge.net/packages/make.htm) and install manually

## Compile Slides

### Scripted

TO DO: DON'T DO NOW... see KERI-2

### Manual

Example commands to build raw `.rst` files into a "compiled" HTML page.
These commands are Linux-centric.  More generic commands, in the form of a Makefile, to come.

From the top-level repo directory:

```
cd slides_raw
bourbon install  # This only needs to be done once
cd ..
hovercraft --slide-numbers ./slides_raw/00_00-EXAMPLES.rst ./slides_built/
firefox ./slides_built/index.html  # As one example of what to open and how to open it
```
