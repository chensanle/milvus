// Copyright (C) 2019-2020 Zilliz. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied. See the License for the specific language governing permissions and limitations under the License

#pragma once

#include <memory>
#include <utility>

#include "knowhere/index/vector_index/IndexIVF.h"
#include "knowhere/index/vector_index/gpu/GPUIndex.h"

namespace milvus {
namespace knowhere {

class GPUIVF : public IVF, public GPUIndex {
 public:
    explicit GPUIVF(const int& device_id) : IVF(), GPUIndex(device_id) {
        index_mode_ = IndexMode::MODE_GPU;
    }

    explicit GPUIVF(std::shared_ptr<faiss::Index> index, const int64_t device_id, ResPtr& res)
        : IVF(std::move(index)), GPUIndex(device_id, res) {
        index_mode_ = IndexMode::MODE_GPU;
    }

    void
    Train(const DatasetPtr&, const Config&) override;

    void
    Add(const DatasetPtr&, const Config&) override;

    VecIndexPtr
    CopyGpuToCpu(const Config&) override;

    VecIndexPtr
    CopyGpuToGpu(const int64_t, const Config&) override;

 protected:
    BinarySet
    SerializeImpl(const IndexType&) override;

    void
    LoadImpl(const BinarySet&, const IndexType&) override;

    void
    QueryImpl(
        int64_t, const float*, int64_t, float*, int64_t*, const Config&, const faiss::BitsetView& bitset) override;
};

using GPUIVFPtr = std::shared_ptr<GPUIVF>;

}  // namespace knowhere
}  // namespace milvus
