function []=add_rect(frame_begin,frame_num,seq,show_plot)
  clc; close all;
  if nargin < 5
      show_plot = 1;
  end
  p1 = mfilename('fullpath');
  i=findstr(p1,'/');
  p1=p1(1:i(end));
  cd(p1);
  cd ('../output');
  fp1 = fopen(['res_' num2str(seq)' '.txt'],'r+');
  C = fscanf(fp1,'%d,%d,%d,%d');
  fp2 = fopen(['ground_rect_' num2str(seq) '.txt'],'r+');
  G = fscanf(fp2,'%f,%f,%f,%f');
  fp3 = fopen(['pos_' num2str(seq)' '.txt'],'r+');
  B = fscanf(fp3,'%f %f');

  files = dir(['../color/' num2str(seq) '/']);
  t = 0;
  for i=1:numel(files)
      s = regexp(files(i).name,'\.','split')
      if(size(s{1,2})>=1)
          if(strcmp(s{1,2},'jpg') && (str2num(s{1,1})>=frame_begin) && (str2num(s{1,1})<(frame_begin+frame_num)) )
              t = t + 1;
              box1 = [floor(C(4*t-2)-C(3)/2),floor(C(4*t-3)-C(4)/2),C(3),C(4)];
              im = imread(['../color/' num2str(seq) '/' files(i).name]);
              if(show_plot)
                  imshow(im);
                  rect_h = rectangle('Position', box1, 'LineWidth', 1, 'EdgeColor','g');

                  C1(t) = floor(C(4*t-2)-C(3)/2);
                  C2(t) = floor(C(4*t-3)-C(4)/2);
                  G1(t) = G(4*(t+frame_begin-1)-3);
                  G2(t) = G(4*(t+frame_begin-1)-2);
                  B1(t) = floor(B(2*t)-C(3)/2);
                  B2(t) = floor(B(2*t-1)-C(4)/2);
              end
          end
      end
  end

  close all;
  if(show_plot)
      figure(1);
      hold on;
      plot(frame_begin:frame_begin+frame_num-1,C1,'g');
      plot(frame_begin:frame_begin+frame_num-1,C2,'b');
      plot(frame_begin:frame_begin+frame_num-1,G1,'r');
      plot(frame_begin:frame_begin+frame_num-1,G2,'k');
      plot(frame_begin:frame_begin+frame_num-1,B1,'c');
      plot(frame_begin:frame_begin+frame_num-1,B2,'m');

      legend('C横坐标','C纵坐标','真实横坐标','真实纵坐标','M横坐标','M纵坐标');
      xlabel('帧号');
      ylabel('位置');
      title(['序列' num2str(seq) 'linear']);

      time = clock;
      hour = floor( time(4) );
      fen  = floor( time(5) );
      saveas(gcf, ['./对比结果_序列' num2str(seq) '_' 'linear' '_' num2str(hour) num2str(fen)], 'png');
  end
  endl= 1
end
