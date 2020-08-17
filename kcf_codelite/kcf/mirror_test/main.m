
function []=main(frame_begin,frame_num,seq,feature_type)
  if (nargin < 4)
    frame_begin = 1;
    frame_num =101;
    seq = 2;
    feature_type = 'linear';
  end

  if(seq==1)
    para1();
  elseif(seq==2)
    para2();
  end

  global gt0
  global gt1
  global gt2
  global gt3
  global padding
  global ifr
  global cell_size
  global lambda
  global sigma
  global output_sigma_factor
  global im_p
  global im_w
  global im_h
  global box_w
  global box_h
  global AA
  global BB
  window_sz = [box_h box_w];
  gauss = zeros(box_h,box_w);

  addpath('./m_kcf');
  addpath('./mexa64');
  addpath('../unit_test')
  hann2 = hann(box_h) * hann(box_w)';
  pos1= [gt1 + floor(gt3/2)  gt0 + floor(gt2/2)];
  pos2= [gt1 + floor(gt3/2)  gt0 + floor(gt2/2)];

  output_sigma = sqrt(gt2*gt3) * output_sigma_factor / cell_size;

  labels1 = gaussian_shaped_labels(output_sigma, ceil(window_sz / cell_size));
  labels2 = mex_gaussian_shaped_labels(gauss);
  step_i = 1;
  res = compare(labels1,labels2);
  if(res == 1)
    fprintf('%s %d %s\n',"step",step_i,"success");
  else
    fprintf('%s %d %s\n',"step",step_i,"fail");
  end
  step_i = step_i + 1;

   yf1 = fft2(labels1);
   yf2 = mex_fft2_d(labels2,box_w,box_h);
   res = compare(yf1,yf2);
   if(res == 1)
     fprintf('%s %d %s\n',"step",step_i,"success");
   else
     fprintf('%s %d %s\n',"step",step_i,"fail");
   end
   step_i = step_i + 1;

  for frame = frame_begin:(frame_begin+frame_num-1)
    im1 = imread(['../color/' num2str(seq) '/' num2str(frame,'%08d') '.jpg']);
    im1 =double(rgb2gray(im1));
    im2 = zeros(size(im1,1),size(im1,2));
    im2 = mex_data_input(im2,['../color/' num2str(seq) '/' num2str(frame,'%08d') '.txt']);
    res = compare(im1,im2);
    if(res == 1)
      fprintf('%s %d %s\n',"step",step_i,"success");
    else
      fprintf('%s %d %s\n',"step",step_i,"fail");
    end
    step_i = step_i + 1;

    if (frame == frame_begin)
      patch1 = get_subwindow(im1, pos1,window_sz);
      patch2 = mex_get_subwindow(im2,pos2);
      res = compare(patch1,patch2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      features.hog =false; features.gray=true;
      feature1 = get_features(patch1, features, cell_size, hann2);
      feature2 = mex_get_features(patch2, hann2);
      res = compare(feature1,feature2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      xf1 = fft2(feature1);
      xf2 = mex_fft2_d(feature2,box_w,box_h);
      res = compare(xf1,xf2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;
      switch feature_type
      case 'gaussian',
        kf1 = gaussian_correlation(xf1, xf1, sigma);
        kf2 = mex_gaussian_correlation(xf2, xf2);
      case 'polynomial',
        kf1 = polynomial_correlation(xf1, xf1, AA, BB);
        kf2 = mex_polynomial_correlation(xf2, xf2);
      case 'linear',
        kf1 = linear_correlation(xf1, xf1);
        kf2 = mex_linear_correlation(xf2, xf2);
      end
      res = compare(kf1,kf2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      alphaf1 = yf1 ./ (kf1 + lambda);
      alphaf2 = yf2 ./ (kf2 + lambda);
      % alphaf2 = mex_div_f(yf2, kf2+ lambda);
      res = compare(alphaf1,alphaf2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      model_alphaf1 = alphaf1;
      model_xf1 = xf1;
      model_alphaf2 = alphaf2;
      model_xf2 = xf2;
    end
    if (frame > frame_begin)
      patch1 = get_subwindow(im1, pos1,window_sz);
      patch2 = mex_get_subwindow(im2, pos2);
      res = compare(patch1,patch2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      features.hog =false; features.gray=true;
      feature1 = get_features(patch1, features, cell_size, hann2);
      feature2 = mex_get_features(patch2, hann2);
      res = compare(feature1,feature2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      zf1 = fft2(feature1);
      zf2 = mex_fft2_d(feature2,box_w,box_h);
      res = compare(zf1,zf2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;
      switch feature_type
      case 'gaussian',
        kzf1 = gaussian_correlation(zf1, model_xf1, sigma);
        kzf2 = mex_gaussian_correlation(zf2, model_xf2);
      case 'polynomial',
        kzf1 = polynomial_correlation(zf1, model_xf1, AA, BB);
        kzf2 = mex_polynomial_correlation(zf2, model_xf2);
      case 'linear',
        kzf1 = linear_correlation(zf1, model_xf1);
        kzf2 = mex_linear_correlation(zf2, model_xf2);
      end
      res = compare(kzf1,kzf2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      mf1 = model_alphaf1 .* kzf1;
      mf2 = mex_mul_f(model_alphaf2, kzf2);
      res = compare(mf1,mf2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      response1 = real(ifft2(mf1));
      response2 = real(mex_ifft2(mf2,box_w,box_h));
      res = compare(response1,response2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      [vert_delta1, horiz_delta1] = find(response1 == max(response1(:)), 1);
      [vert_delta2, horiz_delta2] = find(response2 == max(response2(:)), 1);
      if(vert_delta1 > box_h/2)
        vert_delta1 = vert_delta1 - box_h;
      end
      if(vert_delta2 > box_h/2)
        vert_delta2 = vert_delta2 - box_h;
      end
      if(horiz_delta1 > box_w/2)
        horiz_delta1 = horiz_delta1 - box_w;
      end
      if(horiz_delta2 > box_w/2)
        horiz_delta2 = horiz_delta2 - box_w;
      end
      pos1 = pos1 + cell_size * [vert_delta1 - 1, horiz_delta1 - 1];
      pos2 = pos2 + cell_size * [vert_delta2 - 1, horiz_delta2 - 1];
      res = compare(pos1,pos2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      patch1 = get_subwindow(im1, pos1,window_sz);
      patch2 = mex_get_subwindow(im2, pos2);
      res = compare(patch1,patch2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      features.hog =false; features.gray=true;
      feature1 = get_features(patch1, features, cell_size, hann2);
      feature2 = mex_get_features(patch2, hann2);
      res = compare(feature1,feature2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      xf1 = fft2(feature1);
      xf2 = mex_fft2_d(feature2,box_w,box_h);
      res = compare(xf1,xf2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      switch feature_type
      case 'gaussian',
        kf1 = gaussian_correlation(xf1, xf1, sigma);
        kf2 = mex_gaussian_correlation(xf2, xf2);
      case 'polynomial',
        kf1 = polynomial_correlation(xf1, xf1, AA, BB);
        kf2 = mex_polynomial_correlation(xf2, xf2);
      case 'linear',
        kf1 = linear_correlation(xf1, xf1);
        kf2 = mex_linear_correlation(xf2, xf2);
      end
      res = compare(kf1,kf2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      alphaf1 = yf1 ./ (kf1 + lambda);
      alphaf2 = yf2 ./ (kf2 + lambda);
      % alphaf2 = mex_div_f(yf2, kf2+ lambda);
      res = compare(alphaf1,alphaf2);
      if(res == 1)
        fprintf('%s %d %s\n',"step",step_i,"success");
      else
        fprintf('%s %d %s\n',"step",step_i,"fail");
      end
      step_i = step_i + 1;

      model_alphaf1 = (1 - ifr) * model_alphaf1 + ifr * alphaf1;
      model_alphaf2 = (1 - ifr) * model_alphaf2 + ifr * alphaf2;

      model_xf1 = (1 - ifr) * model_xf1 + ifr * xf1;
      model_xf2 = (1 - ifr) * model_xf2 + ifr * xf2;
    end

    if(frame == frame_begin)
        out_name1 = "res_1.txt";
        out_name2 = "res_2.txt";
        fp1 = fopen(out_name1,"w");
        fp2 = fopen(out_name2,"w");
        if(fp1 == 0)
          fprinf("file open error!");
        end
        if(fp2 == 0)
          fprinf("file open error!");
        end
    end
    fprintf(fp1,"%d,%d,%d,%d\n",pos1(1),pos1(2),gt2,gt3);
    fprintf(fp2,"%d,%d,%d,%d\n",pos2(1),pos2(2),gt2,gt3);
    fprintf("seq=%d,type=%s,frame=%d\n",seq,feature_type,frame);
  end
  fclose(fp1);
  fclose(fp2);
  endl = 1
end
