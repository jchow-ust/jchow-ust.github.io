class MyDataset(Dataset):

    def __init__(self, folders, transform=None):
        self.folders, self.labels = self.get_labels(folders)
        self.transform = transform

    def __len__(self):
        return len(self.folders)
    
    def __getitem__(self, idx):
        folder_id = self.folders[idx]
        
        try:
            with open(folder_id, 'rb') as f:
                color_img = pickle.load(f)
        except EOFError:
            print(folder_id)

        # img process
        for i in range(color_img.shape[0]):
            if np.ptp(color_img[i, :, :]) != 0:
                color_img[i,:,:] = (color_img[i,:,:] - np.min(color_img[i,:,:])) / np.ptp(color_img[i,:,:])
        color_img = color_img.transpose((1,2,0))

        # img process
        c1 = color_img[:,:,0]
        c2 = color_img[:,:,1]
        c3 = color_img[:,:,2]
        c4 = color_img[:,:,3]
        
        c1 = np.expand_dims(c1, axis=2)
        c2 = np.expand_dims(c2, axis=2)
        c3 = np.expand_dims(c3, axis=2)
        c4 = np.expand_dims(c4, axis=2)

        color_img = np.concatenate((c1, c2, c3, c4), axis=2)
        for i in range(color_img.shape[2]):
            if np.ptp(color_img[:,:,i]) == 0:
                continue
            color_img[:,:,i] = (color_img[:,:,i] - np.min(color_img[:,:,i])) / np.ptp(color_img[:,:,i])

        # img process, tranform
        if self.transform is not None:
            color_img = np.uint8(255*color_img)
            color_img = Image.fromarray(color_img)
            color_img = self.transform(color_img)

        return color_img, self.labels[idx]


    def get_labels(self, folders):

        files = []
        labels = []

        #conding=utf8  
        g = os.walk(folders)  

        for path, _, file_list in g:  
            for file_name in file_list:
                files.append(os.path.join(path, file_name))
                if 'nil_HS_H08' in file_name or 'light_HS_H08' in file_name:
                    labels.append(0)
                elif 'moderate_HS_H08' in file_name:
                    labels.append(1)
                else:
                    labels.append(2)
                
        return files, labels