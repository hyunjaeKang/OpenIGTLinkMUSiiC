cd ('C:\Users\HYKang\Documents\10_MyWorks\02_Develop2015\10_OpenIGTLinkMUSiiC\00_Build_Static\Examples\42_MUSiiCStreamWriter3\18_36_28_DAQ__B\')

File1 = 'B000_Bind_000_FirstImage.igtl';
File2 = 'B000_Bind_001_SecondImage.igtl';
File3 = 'B000_Bind_002_ThridImage.igtl';

Img1 = ReadSingleIGTLMsg(File1);
Img2 = ReadSingleIGTLMsg(File2);
Img3 = ReadSingleIGTLMsg(File3);

figure;
subplot(1,3,1);
imagesc(Img1.Body.data);
axis image;
colormap(gray);
title('1st Image');


subplot(1,3,2);
imagesc(Img2.Body.data);
axis image;
colormap(gray);
title('2nd Image');

subplot(1,3,3);
imagesc(Img3.Body.data);
axis image;
colormap(gray);
title('3rd Image');