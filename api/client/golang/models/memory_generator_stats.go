// Code generated by go-swagger; DO NOT EDIT.

package models

// This file was generated by the swagger tool.
// Editing this file might prove futile when you re-run the swagger generate command

import (
	"context"

	"github.com/go-openapi/errors"
	"github.com/go-openapi/strfmt"
	"github.com/go-openapi/swag"
	"github.com/go-openapi/validate"
)

// MemoryGeneratorStats Memory generator statistics
//
// swagger:model MemoryGeneratorStats
type MemoryGeneratorStats struct {

	// The actual number of bytes read or written
	// Required: true
	BytesActual *int64 `json:"bytes_actual"`

	// The intended number of bytes read or written
	// Required: true
	BytesTarget *int64 `json:"bytes_target"`

	// The number of io_errors observed during reading or writing
	// Required: true
	IoErrors *int64 `json:"io_errors"`

	// The maximum observed latency value (in nanoseconds)
	LatencyMax int64 `json:"latency_max,omitempty"`

	// The minimum observed latency value (in nanoseconds)
	LatencyMin int64 `json:"latency_min,omitempty"`

	// The total amount of time required to perform all operations (in nanoseconds)
	// Required: true
	LatencyTotal *int64 `json:"latency_total"`

	// The actual number of operations performed
	// Required: true
	OpsActual *int64 `json:"ops_actual"`

	// The intended number of operations performed
	// Required: true
	OpsTarget *int64 `json:"ops_target"`
}

// Validate validates this memory generator stats
func (m *MemoryGeneratorStats) Validate(formats strfmt.Registry) error {
	var res []error

	if err := m.validateBytesActual(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateBytesTarget(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateIoErrors(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateLatencyTotal(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateOpsActual(formats); err != nil {
		res = append(res, err)
	}

	if err := m.validateOpsTarget(formats); err != nil {
		res = append(res, err)
	}

	if len(res) > 0 {
		return errors.CompositeValidationError(res...)
	}
	return nil
}

func (m *MemoryGeneratorStats) validateBytesActual(formats strfmt.Registry) error {

	if err := validate.Required("bytes_actual", "body", m.BytesActual); err != nil {
		return err
	}

	return nil
}

func (m *MemoryGeneratorStats) validateBytesTarget(formats strfmt.Registry) error {

	if err := validate.Required("bytes_target", "body", m.BytesTarget); err != nil {
		return err
	}

	return nil
}

func (m *MemoryGeneratorStats) validateIoErrors(formats strfmt.Registry) error {

	if err := validate.Required("io_errors", "body", m.IoErrors); err != nil {
		return err
	}

	return nil
}

func (m *MemoryGeneratorStats) validateLatencyTotal(formats strfmt.Registry) error {

	if err := validate.Required("latency_total", "body", m.LatencyTotal); err != nil {
		return err
	}

	return nil
}

func (m *MemoryGeneratorStats) validateOpsActual(formats strfmt.Registry) error {

	if err := validate.Required("ops_actual", "body", m.OpsActual); err != nil {
		return err
	}

	return nil
}

func (m *MemoryGeneratorStats) validateOpsTarget(formats strfmt.Registry) error {

	if err := validate.Required("ops_target", "body", m.OpsTarget); err != nil {
		return err
	}

	return nil
}

// ContextValidate validates this memory generator stats based on context it is used
func (m *MemoryGeneratorStats) ContextValidate(ctx context.Context, formats strfmt.Registry) error {
	return nil
}

// MarshalBinary interface implementation
func (m *MemoryGeneratorStats) MarshalBinary() ([]byte, error) {
	if m == nil {
		return nil, nil
	}
	return swag.WriteJSON(m)
}

// UnmarshalBinary interface implementation
func (m *MemoryGeneratorStats) UnmarshalBinary(b []byte) error {
	var res MemoryGeneratorStats
	if err := swag.ReadJSON(b, &res); err != nil {
		return err
	}
	*m = res
	return nil
}
