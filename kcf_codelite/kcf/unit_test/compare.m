
function res = compare(input1,input2)
  epison = 0.001;
  flag = 0;
  if(size(input1)~=size(input2))
    res = 0;
  else
    temp = abs(input1 - input2);
    for i=1:numel(temp)
     if (temp(i) > epison)
       flag = 1;
     end
    end
    if flag==1
      res =0;
    else
      res=1;
    end
  end
end
