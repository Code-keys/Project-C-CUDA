import torch
import struct

# Initialize
device = torch.device('cuda:0')
# Load model
model = torch.load('/media/cx/UBUNTU 18_0/cp_s/cp_s.pt', map_location=device)[
    'model'].float()  # load to FP32
model.to(device).eval()

f = open('/home/cx/tensorrtx-v7/yolov5/yolov5s.wts', 'w')
f.write('{}\n'.format(len(model.state_dict().keys())))
for k, v in model.state_dict().items():
    vr = v.reshape(-1).cpu().numpy()
    f.write('{} {} '.format(k, len(vr)))
    for vv in vr:
        f.write(' ')
        f.write(struct.pack('>f', float(vv)).hex())
    f.write('\n')
