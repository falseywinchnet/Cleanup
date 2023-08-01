# Cleanup 
Cleanup is a novel DSP algorithm for denoising speech. Cleanup is Open Source Freeware with no warrantee or support.\
It is designed to work primarily on radio- shortwave, FM, VHF, UHF. It does beat any AI currently on the market,
with the understanding that AI is not typically well tuned for shortwave use and thus algorithms are better.\
It is designed to work at a 48hkz input rate, but the core algorithm can be adapted for use at 6,12,and 24k rates.\
The use of a notch filter(carrier suppression) and AGC is highly advised before this algorithm in the pipeline.\
Other noise filtration methods should be placed before cleanup.\



![Cleanup User Interface Photo](https://i.imgur.com/465sJq4.png)

All the interface options in the vst3 have tooltip instructions.\
To ensure audacity compatibility, vst3 does not have support for direct parameter settings.
