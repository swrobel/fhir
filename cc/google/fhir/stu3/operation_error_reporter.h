/*
 * Copyright 2021 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GOOGLE_FHIR_STU3_OPERATION_ERROR_REPORTER_H_
#define GOOGLE_FHIR_STU3_OPERATION_ERROR_REPORTER_H_

#include "absl/status/status.h"
#include "google/fhir/error_reporter.h"
#include "proto/google/fhir/proto/stu3/resources.pb.h"
#include "proto/google/fhir/proto/stu3/codes.pb.h"
#include "proto/google/fhir/proto/stu3/datatypes.pb.h"

namespace google {
namespace fhir {
namespace stu3 {

// Error reporter that creates FHIR STU3 OperationOutcome records.
// Conversion issues that can result in data loss are reported as a "structure"
// error type as described at https://www.hl7.org/fhir/valueset-issue-type.html,
// since the item could not be converted into the target structure. Validation
// issues that preserve data use a "value" error type from that value set.
class OperationOutcomeErrorReporter : public ErrorReporter {
 public:
  explicit OperationOutcomeErrorReporter(
      ::google::fhir::stu3::proto::OperationOutcome* outcome)
      : outcome_(outcome) {}

  absl::Status ReportConversionError(absl::string_view element_path,
                           const absl::Status& error_status) override;

  absl::Status ReportValidationError(absl::string_view element_path,
                           const absl::Status& error_status) override;

  absl::Status ReportValidationWarning(absl::string_view element_path,
                             const absl::Status& error_status) override;
 private:
  absl::Status Report(absl::string_view element_path,
                      const absl::Status& error_status,
                      ::google::fhir::stu3::proto::IssueTypeCode::Value type,
                      ::google::fhir::stu3::proto::IssueSeverityCode::Value
                      severity);

  ::google::fhir::stu3::proto::OperationOutcome* outcome_;
};

}  // namespace stu3
}  // namespace fhir
}  // namespace google

#endif  // GOOGLE_FHIR_STU3_OPERATION_ERROR_REPORTER_H_
