# WallinCode

## Table of Contents
- [Overview](#overview)
- [Targets](#targets)
- [Target Images](#target_images)
- [Current state](#current)
- [run_multiple script](#run_multiple_script)
- [data_tools](#data_tools)
- [image_creator](#image_creator)
- [comparison_code](#comparison_code)
- [plotting_test](#plotting_test)
- [make_real](#make_real)

## Overview<a id="overview">
This is the development branch of a fork of
[Wallincode](https://github.com/JSPAM-Manga/WallinCode).

The recent developments in this fork of JSPAM-Manga focus on creating a machine
scoring mechanism for comparing
rendered galaxy merger models to the morphology of their real counterparts.
These machine scores can then be used in conjunction with citizen science
efforts to score these same models, effectively reducing the human interaction
time needed to determine whether a particular model is "good" or "bad." Further,
the availability of a machine scoring mechanism will open the door to
incorporation of various machine learning algorithms to throw out bad models,
thereby removing the need for a human-in-the-loop altogether.

<!--## Targets<a id="targets">
Below is a table containing the SDSSID numbers from DR7, as well as the RA and
DEC for each of the targets. The for each target take you to the associated
pages for DR7 and DR14, as well as the Galaxy Zoo page.

<font color="red">THE LINKS ARE INCORRECT AS OF RIGHT NOW! We'll be
fixing that shortly.</font>

<table>
<tr>
	<th>SDSSID</th>
	<th>RA</th>
	<th>DEC</th>
	<th>DR7 Link<br></th>
	<th>DR14 Link<br></th>
	<th>Galaxy Zoo Link<br></th>
</tr>
<tr>
	<td>587722984435351614<br></td>
	<td>204.97033333333334<br></td>
	<td>0.8398444444444445<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587722984435351614">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=204.97033333333334&dec=0.8398444444444445">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587722984435351614">Link</a><br></td>
</tr>
<tr>
	<td>587724234257137777<br></td>
	<td>30.95716666666667<br></td>
	<td>14.738644444444445<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587724234257137777">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=30.95716666666667&dec=14.738644444444445">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587724234257137777">Link</a><br></td>
</tr>
<tr>
	<td>587726033843585146<br></td>
	<td>144.43333333333334<br></td>
	<td>2.760163888888889<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587726033843585146">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=144.43333333333334&dec=2.760163888888889">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587726033843585146">Link</a><br></td>
</tr>
<tr>
	<td>587727177926508595<br></td>
	<td>32.352333333333334<br></td>
	<td>-10.136005555555556<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587727177926508595">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=32.352333333333334&dec=-10.136005555555556">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587727177926508595">Link</a><br></td>
</tr>
<tr>
	<td>587727178988388373<br></td>
	<td>4.708583333333333<br></td>
	<td>-10.361625<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587727178988388373">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=4.708583333333333&dec=-10.361625">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587727178988388373">Link</a><br></td>
</tr>
<tr>
	<td>587727222471131318<br></td>
	<td>322.247278321772<br></td>
	<td>11.3819691919192<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587727222471131318">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=322.247278321772&dec=11.3819691919192">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587727222471131318">Link</a><br></td>
</tr>
<tr>
	<td>587728676861051075<br></td>
	<td>203.04275<br></td>
	<td>62.76733611111111<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587728676861051075">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=203.04275&dec=62.76733611111111">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587728676861051075">Link</a><br></td>
</tr>
<tr>
	<td>587729227151704160<br></td>
	<td>238.28595833333333<br></td>
	<td>54.14735<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587729227151704160">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=238.28595833333333&dec=54.14735">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587729227151704160">Link</a><br></td>
</tr>
<tr>
	<td>587731913110650988<br></td>
	<td>141.01241666666667<br></td>
	<td>49.20393888888889<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587731913110650988">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=141.01241666666667&dec=49.20393888888889">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587731913110650988">Link</a><br></td>
</tr>
<tr>
	<td>587732136993882121<br></td>
	<td>173.1475<br></td>
	<td>53.06667<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587732136993882121">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=173.1475&dec=53.06667">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587732136993882121">Link</a><br></td>
</tr>
<tr>
	<td>587732772130652231<br></td>
	<td>185.74029166666668<br></td>
	<td>10.547975<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587732772130652231">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=185.74029166666668&dec=10.547975">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587732772130652231">Link</a><br></td>
</tr>
<tr>
	<td>587733080814583863<br></td>
	<td>190.95583333333335<br></td>
	<td>54.904561111111114<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587733080814583863">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=190.95583333333335&dec=54.904561111111114">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587733080814583863">Link</a><br></td>
</tr>
<tr>
	<td>587734862680752822<br></td>
	<td>148.286790551545<br></td>
	<td>7.86616717171717<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587734862680752822">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=148.286790551545&dec=7.86616717171717">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587734862680752822">Link</a><br></td>
</tr>
<tr>
	<td>587735043609329845<br></td>
	<td>122.80625<br></td>
	<td>25.206611111111112<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587735043609329845">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=122.80625&dec=25.206611111111112">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587735043609329845">Link</a><br></td>
</tr>
<tr>
	<td>587735665840881790<br></td>
	<td>205.41387500000002<br></td>
	<td>55.67073055555556<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587735665840881790">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=205.41387500000002&dec=55.67073055555556">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587735665840881790">Link</a><br></td>
</tr>
<tr>
	<td>587736941981466667<br></td>
	<td>214.26054166666668<br></td>
	<td>36.57129444444445<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587736941981466667">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=214.26054166666668&dec=36.57129444444445">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587736941981466667">Link</a><br></td>
</tr>
<tr>
	<td>587738569246376675<br></td>
	<td>199.197567444494<br></td>
	<td>14.4276911616162<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587738569246376675">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=199.197567444494&dec=14.4276911616162">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587738569246376675">Link</a><br></td>
</tr>
<tr>
	<td>587738569249390718<br></td>
	<td>206.209975800495<br></td>
	<td>13.9213815656566<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587738569249390718">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=206.209975800495&dec=13.9213815656566">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587738569249390718">Link</a><br></td>
</tr>
<tr>
	<td>587739153356095531<br></td>
	<td>125.89175<br></td>
	<td>21.347327777777778<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739153356095531">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=125.89175&dec=21.347327777777778">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739153356095531">Link</a><br></td>
</tr>
<tr>
	<td>587739407868690486<br></td>
	<td>219.460375<br></td>
	<td>30.483197222222223<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739407868690486">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=219.460375&dec=30.483197222222223">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739407868690486">Link</a><br></td>
</tr>
<tr>
	<td>587739505541578866<br></td>
	<td>179.401874039797<br></td>
	<td>32.2777398989899<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739505541578866">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=179.401874039797&dec=32.2777398989899">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739505541578866">Link</a><br></td>
</tr>
<tr>
	<td>587739646743412797<br></td>
	<td>163.06195833333334<br></td>
	<td>30.05786388888889<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739646743412797">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=163.06195833333334&dec=30.05786388888889">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739646743412797">Link</a><br></td>
</tr>
<tr>
	<td>587739647284805725<br></td>
	<td>174.92683333333335<br></td>
	<td>31.909294444444445<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739647284805725">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=174.92683333333335&dec=31.909294444444445">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739647284805725">Link</a><br></td>
</tr>
<tr>
	<td>587739707420967061<br></td>
	<td>241.38791666666668<br></td>
	<td>17.60128611111111<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739707420967061">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=241.38791666666668&dec=17.60128611111111">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739707420967061">Link</a><br></td>
</tr>
<tr>
	<td>587739721376202860<br></td>
	<td>224.25287500000002<br></td>
	<td>24.617605555555556<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739721376202860">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=224.25287500000002&dec=24.617605555555556">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739721376202860">Link</a><br></td>
</tr>
<tr>
	<td>587739721900163101<br></td>
	<td>191.54225<br></td>
	<td>30.73128888888889<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739721900163101">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=191.54225&dec=30.73128888888889">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739721900163101">Link</a><br></td>
</tr>
<tr>
	<td>587739810496708646<br></td>
	<td>236.742754398445<br></td>
	<td>17.8845815656566<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739810496708646">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=236.742754398445&dec=17.8845815656566">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739810496708646">Link</a><br></td>
</tr>
<tr>
	<td>587739845393580192<br></td>
	<td>241.13225000000003<br></td>
	<td>14.819136111111112<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739845393580192">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=241.13225000000003&dec=14.819136111111112">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739845393580192">Link</a><br></td>
</tr>
<tr>
	<td>587741391565422775<br></td>
	<td>127.99029166666668<br></td>
	<td>19.21122777777778<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587741391565422775">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=127.99029166666668&dec=19.21122777777778">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587741391565422775">Link</a><br></td>
</tr>
<tr>
	<td>587741532784361481<br></td>
	<td>167.80375<br></td>
	<td>28.711780555555556<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587741532784361481">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=167.80375&dec=28.711780555555556">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587741532784361481">Link</a><br></td>
</tr>
<tr>
	<td>587741534400217110<br></td>
	<td>181.43945833333333<br></td>
	<td>31.058611111111112<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587741534400217110">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=181.43945833333333&dec=31.058611111111112">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587741534400217110">Link</a><br></td>
</tr>
<tr>
	<td>587741602030026825<br></td>
	<td>179.69004166666667<br></td>
	<td>27.45203888888889<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587741602030026825">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=179.69004166666667&dec=27.45203888888889">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587741602030026825">Link</a><br></td>
</tr>
<tr>
	<td>587741722819493915<br></td>
	<td>183.89929166666667<br></td>
	<td>28.17772777777778<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587741722819493915">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=183.89929166666667&dec=28.17772777777778">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587741722819493915">Link</a><br></td>
</tr>
<tr>
	<td>587741817851674654<br></td>
	<td>139.172634589767<br></td>
	<td>18.9637111111111<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587741817851674654">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=139.172634589767&dec=18.9637111111111">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587741817851674654">Link</a><br></td>
</tr>
<tr>
	<td>587741829658181698<br></td>
	<td>167.46437500000002<br></td>
	<td>24.26161111111111<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587741829658181698">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=167.46437500000002&dec=24.26161111111111">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587741829658181698">Link</a><br></td>
</tr>
<tr>
	<td>587742010583941189<br></td>
	<td>130.666<br></td>
	<td>14.28561388888889<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587742010583941189">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=130.666&dec=14.28561388888889">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587742010583941189">Link</a><br></td>
</tr>
<tr>
	<td>587742014353702970<br></td>
	<td>175.18370833333333<br></td>
	<td>22.429391666666668<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587742014353702970">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=175.18370833333333&dec=22.429391666666668">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587742014353702970">Link</a><br></td>
</tr>
<tr>
	<td>587742571610243080<br></td>
	<td>166.83683333333335<br></td>
	<td>18.432944444444445<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587742571610243080">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=166.83683333333335&dec=18.432944444444445">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587742571610243080">Link</a><br></td>
</tr>
<tr>
	<td>587745402001817662<br></td>
	<td>141.931125<br></td>
	<td>12.28725<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587745402001817662">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=141.931125&dec=12.28725">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587745402001817662">Link</a><br></td>
</tr>
<tr>
	<td>587746029596311590<br></td>
	<td>157.06933333333333<br></td>
	<td>79.82349166666667<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587746029596311590">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=157.06933333333333&dec=79.82349166666667">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587746029596311590">Link</a><br></td>
</tr>
<tr>
	<td>588011124116422756<br></td>
	<td>198.879642238449<br></td>
	<td>62.1292196969697<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=588011124116422756">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=198.879642238449&dec=62.1292196969697">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#588011124116422756">Link</a><br></td>
</tr>
<tr>
	<td>588013383816904792<br></td>
	<td>181.16466666666668<br></td>
	<td>52.95717777777778<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=588013383816904792">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=181.16466666666668&dec=52.95717777777778">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#588013383816904792">Link</a><br></td>
</tr>
<tr>
	<td>588017604696408086<br></td>
	<td>221.331875<br></td>
	<td>38.73127222222222<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=588017604696408086">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=221.331875&dec=38.73127222222222">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#588017604696408086">Link</a><br></td>
</tr>
<tr>
	<td>588017604696408195<br></td>
	<td>221.32854166666667<br></td>
	<td>38.805725<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=588017604696408195">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=221.32854166666667&dec=38.805725">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#588017604696408195">Link</a><br></td>
</tr>
<tr>
	<td>588017702948962343<br></td>
	<td>222.8720833333333<br></td>
	<td>9.334830555555556<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=588017702948962343">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=222.8720833333333&dec=9.334830555555556">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#588017702948962343">Link</a><br></td>
</tr>
<tr>
	<td>588017978901528612<br></td>
	<td>209.6581666666667<br></td>
	<td>37.42467777777778<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=588017978901528612">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=209.6581666666667&dec=37.42467777777778">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#588017978901528612">Link</a><br></td>
</tr>
<tr>
	<td>588018055130710322<br></td>
	<td>255.02854166666668<br></td>
	<td>23.13154722222222<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=588018055130710322">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=255.02854166666668&dec=23.13154722222222">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#588018055130710322">Link</a><br></td>
</tr>
<tr>
	<td>758874299603222717<br></td>
	<td>0.3614583333333333<br></td>
	<td>31.43341388888889<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=758874299603222717">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=0.3614583333333333&dec=31.43341388888889">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#758874299603222717">Link</a><br></td>
</tr>
<tr>
	<td>587736523764334706<br></td>
	<td>218.78633333333335<br></td>
	<td>5.358805555555556<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587736523764334706">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=218.78633333333335&dec=5.358805555555556">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587736523764334706">Link</a><br></td>
</tr>
<tr>
	<td>587747120521216156<br></td>
	<td>1.686625<br></td>
	<td>-6.636922222222222<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587747120521216156">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=1.686625&dec=-6.636922222222222">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587747120521216156">Link</a><br></td>
</tr>
<tr>
	<td>588007005230530750<br></td>
	<td>116.72070833333333<br></td>
	<td>39.032111111111114<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=588007005230530750">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=116.72070833333333&dec=39.032111111111114">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#588007005230530750">Link</a><br></td>
</tr>
<tr>
	<td>758877153600208945<br></td>
	<td>20.867874999999998<br></td>
	<td>30.784466666666667<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=758877153600208945">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=20.867874999999998&dec=30.784466666666667">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#758877153600208945">Link</a><br></td>
</tr>
<tr>
	<td>587739720308818095<br></td>
	<td>238.403625<br></td>
	<td>18.609608333333334<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=587739720308818095">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=238.403625&dec=18.609608333333334">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#587739720308818095">Link</a><br></td>
</tr>
<tr>
	<td>1237678620102623480<br></td>
	<td>1.0642083333333334<br></td>
	<td>3.3838333333333335<br></td>
	<td><a href="http://cas.sdss.org/dr7/en/tools/explore/obj.asp?id=1237678620102623480">Link</a><br></td>
	<td><a href="http://skyserver.sdss.org/dr14/en/tools/explore/summary.aspx?ra=1.0642083333333334&dec=3.3838333333333335">Link</a><br></td>
	<td><a href="https://data.galaxyzoo.org/galaxy-zoo-mergers/targets/group10/index.html#1237678620102623480">Link</a><br></td>
</tr>
</table>
-->

## Target Images<a id="target_images">
Real images of the target galaxies are contained in the `target_images`
directory. These are to be used as the reference images for comparison in testing.

To my knowledge, the original dataset is based off of images from SDSS DR7, but
the image directory will contain processed images of those same targets using
data from SDSS DR14.


## Current State of Things<a id="current">
Currently, [run_multiple](#run_multiple_script) is set up to complete runs of
basic_run interactively.

There is now a Python [data_tools](#data_tools) package that contains
- structure.py: This is a general_purpose directory structure creator.
- get_target_data.py: This is a module that scrapes the mergers.html page
for links to the zipped target data files. This may not belong in the package,
but as of right now that is its home.

A C++ image_creator and comparison code have also been added.

## run_multiple script<a id="run_multiple_script">
This fork of WallinCode contains run_multiple, a python3 script that runs
specific runs or specific ranges of runs from the Overlapping galaxy pairs
table at
[https://data.galaxyzoo.org/mergers.html](https://data.galaxyzoo.org/mergers.html).
I suggest placing the data files in a directory within the working directory
and copying the necessary files from the input directory when needed.

To use run_multiple, enter

`./run_multiple file_containing_data.txt`

The script will then ask if you want to run only one run from the file or multiple.
Then you will be asked for the run numbers for a specific range of runs. The run
numbers correspond to the line number in the file. The output files are then
organized in the following way:

`./ouput/target_name(which is really the filename preceeding the extension)/run_number`

## data_tools<a id="data_tools">
This is a package that will contain any data tools that can be written as a
general purpose tool. Right now, it contains
- structure.py: This is a general_purpose directory structure creator.
- get_target_data.py: This is a module that scrapes the mergers.html page
for links to the zipped target data files. This may not belong in the package,
but as of right now that is its home.

## image_creator<a id="image_creator">

## comparison_code<a id="comparison_code">

## plotting_test<a id="plotting_test">
This is the temporary name of a python3 script that will produce 2D and 3D plots
of a particular time step. It takes one argument as shown below:

`./plotting_test a.101`

I recommend symlinking plotting_test in general to

`./output/target/run_number/.`

where the data files for each time step are located (i.e. a.000, a.001, ...).
This directory structure is created by **run_multiple**.

There is also an option to produce a gif of the 3D runs (not working at the
moment, not sure what the problem is.)

## make_real<a id="make_real">
This is a python script that intends to produce realistic images of a galaxy end
state output. As of right now, it is in the beginning stages and only calls a
simple gaussian filter over the whole image and a median filter.

# Notes
All development is currently being done on the
[development](https://github.com/jacksonlanecole/WallinCode/tree/development)
branch of this fork. Check it out there!
